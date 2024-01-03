#include "connectionhandler.h"
#include "packetbuilder.h"
#include "serverinformation.h"

#include <QDebug>
#include <QWebSocket>
#include <QWebSocketServer>

ConnectionHandler::ConnectionHandler(QObject *parent, ServerInformation *f_information)
    : QObject{parent}
    , information(f_information)
{
    if (f_information == nullptr) {
        qDebug() << "ServerInformation pointer is nullptr. This is a bad thing to happen.";
    }
    routes["GAME"] = &ConnectionHandler::gameSocketConnected;
    routes["DATA"] = &ConnectionHandler::probeSocketConnected;
}

bool ConnectionHandler::start(QHostAddress f_bind, int f_ws_port)
{
    ws_server = new QWebSocketServer(information->name, QWebSocketServer::NonSecureMode, this);
    if (!ws_server->listen(f_bind, f_ws_port)) {
        return false;
    }
    qDebug() << "Starting insecure Websocket Server on port" << QString::number(f_ws_port);
    connect(ws_server,
            &QWebSocketServer::newConnection,
            this,
            &ConnectionHandler::onSocketConnect);
    connect(this,
            &ConnectionHandler::probeSocketConnected,
            this,
            &ConnectionHandler::sendServerInformation);
    return true;
}

void ConnectionHandler::onSocketConnect()
{
    QWebSocket *l_socket = ws_server->nextPendingConnection();
    QString route = l_socket->requestUrl().fileName().toUpper();

    if (routes.count(route)) {
        emit(this->*routes[route])(l_socket);
        return;
    }
    qDebug() << "Unable to route connection.";
    l_socket->sendTextMessage(
        PacketBuilder::notificationPacket({"Unknown Route. Disconnecting client."}));
    l_socket->close(QWebSocketProtocol::CloseCodeBadOperation);
    l_socket->deleteLater();
}

void ConnectionHandler::sendServerInformation(QWebSocket *f_socket)
{
    f_socket->sendTextMessage(PacketBuilder::informationPacket(information));
    f_socket->close(QWebSocketProtocol::CloseCodeNormal);
    f_socket->deleteLater();
}
