#include "areamanager.h"
#include "area.h"
#include "client.h"
#include "constants.h"
#include "helper.h"
#include "options.h"
#include "packet_selectarea.h"
#include "packetrelay.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

AreaManager::AreaManager(QObject *parent, PacketRelay *f_relay) :
    QObject{parent},
    relay{f_relay}
{
    connect(f_relay, &PacketRelay::clientSelectArea, this, &AreaManager::onSelectAreaReceived);

    QStringList l_areas = Options::areas();
    for (const QString &l_area : l_areas) {
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
    std::unique_ptr<QFile> l_file = Helper::openFile(Storage::area_storage + f_file + ".json", QIODevice::ReadOnly);
    if (l_file.get() == nullptr) {
        return false;
    }

    QJsonDocument l_area_document = Helper::validateJSON(l_file.get()->readAll());
    if (l_area_document.isNull()) {
        return false;
    }

    if (!l_area_document.isObject()) {
        qDebug() << "Unable to load area. Error: Document is not an object.";
        return false;
    }
    QJsonObject l_area_conf = l_area_document.object();
    // TODO: populate locations.

    Area *l_area = new Area(this);

    l_area->setBackgroundList(readBackgrounds(l_area_conf["backgrounds"].toString()));
    l_area->setCharacterList(readCharacters(l_area_conf["characters"].toString()));
    l_area->setMusicList(readMusicList(l_area_conf["musiclist"].toString()));
    l_area->loadLocations(l_area_conf["locations"]);

    areas.append(l_area);
    l_area->setID(areas.indexOf(l_area));
    return true;
}

void AreaManager::onSelectAreaReceived(Packet *f_packet, Client *f_client)
{
    qDebug() << "Received SelectArea by client" << f_client->id();
    PacketSelectArea *l_packet = static_cast<PacketSelectArea *>(f_packet);
    Area *l_area = areas.at(l_packet->getArea());
}

QStringList AreaManager::readCharacters(const QString &f_file)
{
    std::unique_ptr<QFile> l_file = Helper::openFile(Storage::character_storage + f_file + ".txt", QIODevice::ReadOnly);
    if (l_file.get() == nullptr) {
        return QStringList{};
    }
    QStringList l_characters;
    QTextStream l_stream(l_file.get());
    while (!l_stream.atEnd()) {
        l_characters.append(l_stream.readLine());
    }
    return l_characters;
}

DataTypes::BackgroundList AreaManager::readBackgrounds(const QString &f_file)
{
    std::unique_ptr<QFile> l_file = Helper::openFile(Storage::background_storage + f_file + ".json", QIODevice::ReadOnly);
    if (l_file.get() == nullptr) {
        return DataTypes::BackgroundList{};
    }

    QJsonDocument l_background_document = Helper::validateJSON(l_file.get()->readAll());
    if (l_background_document.isNull()) {
        return DataTypes::BackgroundList{};
    }

    DataTypes::BackgroundList backgrounds;
    QJsonArray l_backgrounds = l_background_document.array();
    for (const auto &l_background_ref : l_backgrounds) {
        if (!l_background_ref.isObject()) {
            continue;
        }

        QJsonObject l_background = l_background_ref.toObject();
        DataTypes::BackgroundInformation l_information;
        l_information.name = l_background["name"].toString();
        QJsonArray l_sides = l_background["sides"].toArray();

        for (const auto &l_side_ref : l_sides) {
            QJsonObject l_side = l_side_ref.toObject();
            QString side = l_side["name"].toString();
            l_information.sides.append(side);
            l_information.images.insert(side, l_side["image"].toString());
            l_information.overlays.insert(side, l_side["overlay"].toString());
        }
    }
    return backgrounds;
}

DataTypes::MusicList AreaManager::readMusicList(const QString f_file)
{
    std::unique_ptr<QFile> l_file = Helper::openFile(Storage::music_storage + f_file + ".json", QIODevice::ReadOnly);
    if (l_file.get() == nullptr) {
        return DataTypes::MusicList{};
    }

    QJsonDocument l_musiclist_document = Helper::validateJSON(l_file.get()->readAll());
    if (l_musiclist_document.isNull()) {
        return DataTypes::MusicList{};
    }

    DataTypes::MusicList musiclist;
    QJsonArray l_musiclist_array = l_musiclist_document.array();
    for (const auto &l_musiclist_category : l_musiclist_array) {
        QJsonObject l_musiclist = l_musiclist_category.toObject();
        QList<QVariant> l_variant_songs = l_musiclist["songs"].toArray().toVariantList();
        QStringList songs;
        for (const QVariant &l_song : l_variant_songs) {
            songs.append(l_song.toString());
        }

        DataTypes::MusicCategory l_category;
        l_category.category = l_musiclist["category"].toString();
        l_category.songs = songs;
    }

    return musiclist;
}
