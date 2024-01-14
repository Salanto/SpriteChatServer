#include "areamanager.h"
#include "packetrelay.h"
#include "constants.h"
#include "options.h"
#include "area.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

AreaManager::AreaManager(QObject *parent, PacketRelay *f_relay) :
    QObject{parent},
    relay{f_relay}
{
    qDebug() << "Creating AreaManager";
    QStringList l_areas = Options::areas();
    for(const QString& l_area : l_areas) {
        qDebug() << "Loading area" << l_area;
        if (!loadAreaFromFile(l_area.toLower())) {
            continue;
        }
    }

    if (areas.isEmpty()) {
        qDebug() << "Areas empty. Creating emergency pylons.";
    }
}

bool AreaManager::loadAreaFromFile(const QString &f_file)
{
    std::unique_ptr<QFile> l_file = openFileR(Storage::area_storage + f_file);
    if (l_file.get() == nullptr) {
        return false;
    }

    Area* l_area = new Area(this);

    QJsonParseError l_error;
    QJsonDocument l_area_document = QJsonDocument::fromJson(l_file.get()->readAll(), &l_error);
    if (l_error.error != QJsonParseError::NoError) {
        qDebug() << "Unable to load area. Error:" << l_error.errorString();
        l_area->deleteLater();
        return false;
    }

    if(!l_area_document.isObject()) {
        qDebug() << "Unable to load area. Error: Document is not an object.";
        l_area->deleteLater();
        return false;
    }

    QJsonObject l_area_conf = l_area_document.object();


    areas.append(l_area);
    l_area->setID(areas.indexOf(l_area));
    return true;
}

QStringList AreaManager::readCharacters(const QString &f_file)
{
    std::unique_ptr<QFile> l_file = openFileR(Storage::area_storage + f_file);
    if (l_file.get() == nullptr) {
        return QStringList{};
    }
}

Datatypes::BackgroundList AreaManager::readBackground(const QString &f_file)
{
    std::unique_ptr<QFile> l_file = openFileR(Storage::area_storage + f_file);
    if (l_file.get() == nullptr) {
        return Datatypes::BackgroundList{};
    }
}

Datatypes::MusicList AreaManager::readMusicList(const QString f_file)
{
    std::unique_ptr<QFile> l_file = openFileR(Storage::area_storage + f_file);
    if (l_file.get() == nullptr) {
        return Datatypes::MusicList{};
    }
}

std::unique_ptr<QFile> AreaManager::openFileR(const QString &f_file)
{
    auto l_file =  std::make_unique<QFile>(f_file);
    if (l_file->open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open file" << l_file->fileName();
        return nullptr;
    }
    return l_file;
}



