#include "hvavconnectionhandler.h"
#include "hvacpackagebuilder.h"
#include "options.h"

#include <QDebug>
#include <QHostAddress>
#include <QWebSocket>
#include <QWebSocketServer>

HVACConnectionHandler::HVACConnectionHandler(QObject *parent, ServerInformation *f_information)
    : QObject{parent}
    , information(f_information)
{
    if (f_information == nullptr) {
        qDebug() << "ServerInformation pointer is nullptr. This is a bad thing to happen.";
    }
}

bool HVACConnectionHandler::start()
{
    ws_server = new QWebSocketServer(Options::server_name(), QWebSocketServer::NonSecureMode, this);
    if (!ws_server->listen(QHostAddress::Any, Options::ws_port())) {
        return false;
    }
    qDebug() << "Starting insecure Websocket Server on port" << QString::number(Options::ws_port());
    connect(ws_server,
            &QWebSocketServer::newConnection,
            this,
            &HVACConnectionHandler::onWebSocketConnect);
    return true;
}

void HVACConnectionHandler::onWebSocketConnect()
{
    QWebSocket *l_socket = ws_server->nextPendingConnection();

    QString route = l_socket->requestUrl().fileName().toLower();
    if (route == "game") {
        emit socketConnected(l_socket);
    }
    sendServerInformation(l_socket);
}

void HVACConnectionHandler::sendServerInformation(QWebSocket *f_socket)
{
    QString value = HVACPackageBuilder::informationPacket(information);
    qDebug() << value;
    f_socket->sendTextMessage(value);
    f_socket->close(QWebSocketProtocol::CloseCodeNormal);
}
