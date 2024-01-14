#include "areamanager.h"
#include "packetrelay.h"
#include "constants.h"
#include "options.h"
#include "helper.h"
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
    std::unique_ptr<QFile> l_file = Helper::openFile(Storage::area_storage + f_file, QIODevice::ReadOnly);
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
    std::unique_ptr<QFile> l_file = Helper::openFile(Storage::character_storage + f_file, QIODevice::ReadOnly);
    if (l_file.get() == nullptr) {
        return QStringList{};
    }
    QStringList l_characters;
    QTextStream l_stream(l_file.get());
    while(!l_stream.atEnd()) {
        l_characters.append(l_stream.readLine());
    }
    return l_characters;
}

Datatypes::BackgroundList AreaManager::readBackground(const QString &f_file)
{
    std::unique_ptr<QFile> l_file = Helper::openFile(Storage::background_storage + f_file, QIODevice::ReadOnly);
    if (l_file.get() == nullptr) {
        return Datatypes::BackgroundList{};
    }
}

Datatypes::MusicList AreaManager::readMusicList(const QString f_file)
{
    std::unique_ptr<QFile> l_file = Helper::openFile(Storage::music_storage + f_file, QIODevice::ReadOnly);
    if (l_file.get() == nullptr) {
        return Datatypes::MusicList{};
    }
}



