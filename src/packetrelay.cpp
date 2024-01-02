#include "packetrelay.h"

PacketRelay::PacketRelay(QObject *parent)
    : QObject{parent}
{
    // For some reason I thought this is a good idea. Technically this is a good idea... I think?
}

void PacketRelay::packetReceived(QString f_data, Client *f_client)
{

}
