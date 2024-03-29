#include "area.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

Area::Area(QObject *parent) :
    QObject{parent}
{}

void Area::setID(const int f_id)
{
    id = f_id;
}

int Area::getID() const
{
    return id;
}

QStringList Area::getCharacterList() const
{
    return characters;
}

void Area::setCharacterList(const QStringList &f_characters)
{
    characters = f_characters;
}

QStringList Area::getBackgroundList() const
{
    return backgrounds.keys();
}

void Area::setBackgroundList(const DataTypes::BackgroundList &f_backgrounds)
{
    backgrounds = f_backgrounds;
}

DataTypes::MusicList *Area::getMusicList()
{
    return &musiclist;
}

void Area::setMusicList(const DataTypes::MusicList &f_musiclist)
{
    musiclist = f_musiclist;
}

bool Area::loadLocations(QJsonValue f_locations)
{
    if (!f_locations.isArray()) {
        qDebug() << "Unable to load locations. List is not an array.";
        return false;
    }

    QJsonArray l_locations = f_locations.toArray();
    for (QJsonValueRef l_location_ref : l_locations) {
        if (!l_location_ref.isObject()) {
            qDebug() << "Unable to load location. Entry is not an object.";
            continue;
        }
        QJsonObject l_location = l_location_ref.toObject();
        Location *location = new Location(this);
        location->setID(locations.size());
        location->setName(l_location["name"].toString());
        location->setBackground(backgrounds.value(l_location["background"].toString()));
        location->setDescription(l_location["description"].toString());
        locations.append(location);
    }

    return true;
}

Location *Area::getLocationByID(const int id) const
{
    if (locations.size() < id) {
        qDebug() << "Unable to access Location at" << id;
        qDebug() << "Location does not exist.";
        return nullptr;
    }
    return locations.at(0);
}
