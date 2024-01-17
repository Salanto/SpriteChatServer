#include "clientmanager.h"
#include "client.h"
#include "connectionhandler.h"
#include "options.h"
#include "packetbuilder.h"
#include "packetrelay.h"
#include "serverinformation.h"

#include <QWebSocket>

const int INVALIDID = -1;

ClientManager::ClientManager(QObject *parent, ServerInformation *f_information, PacketRelay *f_relay) :
    QObject{parent},
    s_information{f_information},
    relay{f_relay}
{
    clients.fill(nullptr, Options::max_players());
    connection_handler = new ConnectionHandler(this, s_information);
    connect(connection_handler,
            &ConnectionHandler::gameSocketConnected,
            this,
            &ClientManager::clientConnected);
    connection_handler->start(Options::bind_ip(), Options::ws_port());
    connect(this, &ClientManager::dataReady, relay, &PacketRelay::packetReceived);
    connect(relay, &PacketRelay::unicastSend, this, &ClientManager::unicastSend);
    connect(relay, &PacketRelay::multicastSend, this, &ClientManager::multicastSend);
    connect(relay, &PacketRelay::broadcastSend, this, &ClientManager::broadcastSend);
}

void ClientManager::clientConnected(QWebSocket *f_socket)
{
    // TODO: Add ban checks here
    int l_id = clients.indexOf(nullptr);
    if (l_id == INVALIDID) {
        f_socket->sendBinaryMessage(
            PacketBuilder::notificationPacket({"Unable to join. We're full."}));
        f_socket->close(QWebSocketProtocol::CloseCodeAbnormalDisconnection);
        f_socket->deleteLater();
    }
    Client *l_client = new Client(this, f_socket, l_id);
    clients.insert(l_id, l_client);
    connect(l_client, &Client::networkDataReceived, this, &ClientManager::dataReady);
    connect(l_client, &Client::socketDisconnected, this, &ClientManager::clientDisconnected);
    s_information->playercount++;
}

void ClientManager::clientDisconnected(Client *f_client)
{
    f_client->deleteLater();
    int l_id = clients.indexOf(f_client);
    clients[l_id] = nullptr;
    s_information->playercount--;
}

void ClientManager::unicastSend(const int f_id, const QByteArray f_data)
{
    Client *l_client = clients.at(f_id);
    if (l_client == nullptr) {
        qDebug() << "Unable to send packet to client" << f_id << ". Client does not exist!";
        return;
    }
    l_client->write(f_data);
}

void ClientManager::multicastSend(const QList<int> f_id, const QByteArray f_data)
{
    for (int l_id : f_id) {
        unicastSend(l_id, f_data);
    }
}

void ClientManager::broadcastSend(const QByteArray f_data)
{
    // TODO: This code sucks. We should be able to get the indices of all non-nullptr entries.
    for (Client *l_client : clients) {
        if (l_client != nullptr) {
            l_client->write(f_data);
        }
    }
}
