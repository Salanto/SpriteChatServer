#include "packetrelay.h"

PacketRelay::PacketRelay(QObject *parent)
    : QObject{parent}
{
    routes["HELLO"] = &PacketRelay::softwareInformation;
}

void PacketRelay::packetReceived(QString f_data, Client *f_client)
{

}
