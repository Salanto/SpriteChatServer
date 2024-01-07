#include "areamanager.h"
#include "packetrelay.h"

AreaManager::AreaManager(QObject *parent, PacketRelay *f_relay) :
    QObject{parent},
    relay{f_relay}
{

}
