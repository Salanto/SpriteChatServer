#include "packetrelay.h"
#include "packet/packetfactory.h"

#include "client.h"

PacketRelay::PacketRelay(QObject *parent) :
    QObject{parent}
{
    PacketFactory::registerPackets();
    routes["HELLO"] = &PacketRelay::clientHello;
    routes["SELECT_AREA"] = &PacketRelay::clientSelectArea;
}

void PacketRelay::routeInternalPacket(Packet *f_packet, Client *f_client)
{
    const QString l_header = f_packet->header();
    qDebug() << "Routing internal packet for" << f_client->id() << "at" << f_client->getIP();
    if (canRoutePacket(l_header)) {
        emit(this->*routes[l_header])(f_packet, f_client);
        return;
    }
}

void PacketRelay::packetReceived(QByteArray f_data, Client *f_client)
{
    Packet *f_packet = PacketFactory::createPacket(f_data);
    QString l_header = f_packet->header();

    if (canRoutePacket(l_header)) {
        emit(this->*routes[l_header])(f_packet, f_client);
        return;
    }
    qDebug() << QString("[%1]Unable to route packet with header %2")
                    .arg(QString::number(f_client->id()), f_packet->header());
    delete f_packet;
}

bool PacketRelay::canRoutePacket(QString f_header)
{
    return routes.count(f_header);
}
