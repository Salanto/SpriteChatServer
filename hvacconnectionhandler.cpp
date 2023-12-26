#include "hvacconnectionhandler.h"
#include "hvacpacketbuilder.h"
#include "hvacserverinformation.h"

#include <QDebug>
#include <QWebSocket>
#include <QWebSocketServer>

HVACConnectionHandler::HVACConnectionHandler(QObject *parent, ServerInformation *f_information)
    : QObject{parent}
    , information(f_information)
{
    if (f_information == nullptr) {
        qDebug() << "ServerInformation pointer is nullptr. This is a bad thing to happen.";
    }
    routes["GAME"] = &HVACConnectionHandler::gameSocketConnected;
    routes["DATA"] = &HVACConnectionHandler::probeSocketConnected;
}

bool HVACConnectionHandler::start(QHostAddress f_bind, int f_ws_port)
{
    ws_server = new QWebSocketServer(information->name, QWebSocketServer::NonSecureMode, this);
    if (!ws_server->listen(f_bind, f_ws_port)) {
        return false;
    }
    qDebug() << "Starting insecure Websocket Server on port" << QString::number(f_ws_port);
    connect(ws_server,
            &QWebSocketServer::newConnection,
            this,
            &HVACConnectionHandler::onSocketConnect);
    connect(this,
            &HVACConnectionHandler::probeSocketConnected,
            this,
            &HVACConnectionHandler::sendServerInformation);
    return true;
}

void HVACConnectionHandler::onSocketConnect()
{
    QWebSocket *l_socket = ws_server->nextPendingConnection();
    QString route = l_socket->requestUrl().fileName().toUpper();

    if (routes.count(route)) {
        emit(this->*routes[route])(l_socket);
        return;
    }
    qDebug() << "Unable to route connection.";
    l_socket->close(QWebSocketProtocol::CloseCodeBadOperation);
}

void HVACConnectionHandler::sendServerInformation(QWebSocket *f_socket)
{
    f_socket->sendTextMessage(HVACPacketBuilder::informationPacket(information));
    f_socket->close(QWebSocketProtocol::CloseCodeNormal);
}
