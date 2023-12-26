#include "hvacpacketbuilder.h"
#include "hvacserverinformation.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QByteArray HVACPacketBuilder::informationPacket(ServerInformation *f_content)
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
