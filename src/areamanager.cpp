#include "areamanager.h"
#include "packetrelay.h"
#include "constants.h"
#include "areadata.h"

#include <QFile>
#include <QDebug>

AreaManager::AreaManager(QObject *parent, PacketRelay *f_relay) :
    QObject{parent},
    relay{f_relay}
{
    QString l_file_path = Storage::area_storage + "default.json";
    QFile l_area_file(l_file_path);
    if (!l_area_file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to load arealist.";
        qDebug() << "Creating emergency area.";
        AreaData* l_area = new AreaData(0);
        areas.append(l_area);
        l_area->setName("Default");
        l_area->setBackground("default", {"wit"});
        return;
    }
    return;
}

void AreaManager::loadAreasFromFile(const QString &f_filename)
{

}
