#include "hvacclientmanager.h"
#include "client.h"
#include "hvacconnectionhandler.h"
#include "hvacpacketbuilder.h"
#include "hvacserverinformation.h"
#include "options.h"

#include <QWebSocket>

const int INVALIDID = -1;

HVACClientManager::HVACClientManager(QObject *parent, ServerInformation *f_information)
    : QObject{parent}
    , s_information{f_information}
{
    clients.fill(nullptr, Options::max_players());
    connection_handler = new HVACConnectionHandler(this, s_information);
    connect(connection_handler,
            &HVACConnectionHandler::gameSocketConnected,
            this,
            &HVACClientManager::clientConnected);
    connection_handler->start(Options::bind_ip(), Options::ws_port());
}

void HVACClientManager::clientConnected(QWebSocket *f_socket)
{
    //TODO: Add ban checks here
    int l_client_id = clients.indexOf(nullptr);
    if (l_client_id == INVALIDID) {
        f_socket->sendTextMessage(
            HVACPacketBuilder::notificationPacket({"Unable to join. We're full."}));
        f_socket->close(QWebSocketProtocol::CloseCodeAbnormalDisconnection);
        f_socket->deleteLater();
    }
    Client *l_client = new Client(this, f_socket, l_client_id);
    clients.append(l_client);
    connect(l_client, &Client::networkDataReceived, this, &HVACClientManager::dataReady);
    s_information->playercount++;
}

void HVACClientManager::clientDisconnected()
{
    s_information->playercount--;
}
