#include "packetbuilder.h"
#include "datatypes.h"
#include "serverinformation.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

// TODO: Optimise repeated code. Two helpers should work fine.)

QByteArray PacketBuilder::informationPacket(ServerInformation *f_content)
{
    QJsonObject l_root_obj;

    QJsonObject l_data;
    l_data["application"] = f_content->app_name;
    l_data["version"] = f_content->app_version.toString();
    l_data["name"] = f_content->name;
    l_data["description"] = f_content->description;
    l_data["playercount"] = f_content->playercount;
    l_data["url"] = f_content->asset_url;

    QJsonArray l_packages = QJsonArray::fromStringList(f_content->package_ids);
    l_data["packages"] = l_packages;

    l_root_obj["header"] = "server_hello";
    l_root_obj["data"] = l_data;
    QJsonDocument l_json_document(l_root_obj);
    return l_json_document.toJson(QJsonDocument::Compact);
}

QByteArray PacketBuilder::notificationPacket(QStringList messages)
{
    QJsonObject l_root_obj;
    l_root_obj["header"] = "notification";
    l_root_obj["data"] = QJsonArray::fromStringList(messages);

    QJsonDocument l_json_document(l_root_obj);
    return l_json_document.toJson(QJsonDocument::Compact);
}

QByteArray PacketBuilder::backgroundPacket(DataTypes::BackgroundInformation *f_content, bool f_reset)
{
    QJsonObject l_data_obj;
    l_data_obj["name"] = f_content->name;
    l_data_obj["reset"] = f_reset;

    QJsonObject l_root_obj;
    l_root_obj["header"] = "background";
    l_root_obj["data"] = l_data_obj;

    QJsonDocument l_json_document(l_root_obj);
    return l_json_document.toJson(QJsonDocument::Compact);
}

QByteArray PacketBuilder::sidesPacket(DataTypes::BackgroundInformation *f_content)
{
    QJsonArray l_data_array;

    for (const QString &l_side : f_content->sides) {
        QJsonObject l_side_obj;
        l_side_obj["side"] = l_side;
        l_side_obj["image"] = f_content->images[l_side];
        l_side_obj["overlay"] = f_content->overlays[l_side];
        l_data_array.append(l_side_obj);
    }

    QJsonObject l_root_obj;
    l_root_obj["header"] = "sidelist";
    l_root_obj["data"] = l_data_array;

    QJsonDocument l_json_document(l_root_obj);
    return l_json_document.toJson(QJsonDocument::Compact);
}

QByteArray PacketBuilder::musiclistPacket(DataTypes::MusicList *f_content)
{
    QJsonArray l_music_array;

    for (const DataTypes::MusicCategory &l_category : f_content->musiclist) {
        QJsonObject l_music_entry;
        l_music_entry["category"] = l_category.category;
        l_music_entry["songs"] = QJsonArray::fromStringList(l_category.songs);
        l_music_array.append(l_music_entry);
    }

    QJsonObject l_root_obj;
    l_root_obj["header"] = "musiclist";
    l_root_obj["data"] = l_music_array;

    QJsonDocument l_json_document(l_root_obj);
    return l_json_document.toJson(QJsonDocument::Compact);
}

QByteArray PacketBuilder::charlistPacket(QStringList f_content)
{
    QJsonObject l_root_obj;
    l_root_obj["header"] = "musiclist";
    l_root_obj["data"] = QJsonArray::fromStringList(f_content);

    QJsonDocument l_json_document(l_root_obj);
    return l_json_document.toJson(QJsonDocument::Compact);
}

QByteArray PacketBuilder::arealistPacket()
{
    QJsonObject l_root_obj;
    l_root_obj["header"] = "arealist";
    l_root_obj["data"] = "";

    QJsonDocument l_json_document(l_root_obj);
    return l_json_document.toJson(QJsonDocument::Compact);
}
