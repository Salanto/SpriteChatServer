#include "areamanager.h"
#include "packetrelay.h"
#include "constants.h"

#include <QFile>
#include <QDebug>

AreaManager::AreaManager(QObject *parent, PacketRelay *f_relay) :
    QObject{parent},
    relay{f_relay}
{

}
