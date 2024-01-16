#include "banmanager.h"
#include "client.h"
#include "packet_hello.h"
#include "packet_selectarea.h"
#include "packetrelay.h"

#include <QDebug>

BanManager::BanManager(QObject *parent, PacketRelay *f_relay) :
    QObject{parent},
    relay{f_relay}
{
    qDebug() << "Creating BanManager";
    connect(relay, &PacketRelay::clientHello, this, &BanManager::onHELLOReceived);
}

void BanManager::onHELLOReceived(Packet *f_packet, Client *f_client)
{
    PacketHello *packet = static_cast<PacketHello *>(f_packet);
    qDebug() << "Received HELLO from ClientID" << f_client->id() << "at" << f_client->getIP().toString();
    qDebug() << "App-Name:" << packet->appName();
    qDebug() << "App-Version:" << packet->appVersion().toString();
    qDebug() << "Identifier:" << packet->hwid();
    delete packet;

    PacketSelectArea *l_packet = new PacketSelectArea();
    l_packet->setArea(0);
    l_packet->setLocation(0);
    relay->routeInternalPacket(l_packet, f_client);
}
