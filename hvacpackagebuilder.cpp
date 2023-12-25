#include "hvacpackagebuilder.h"
#include "hvacserverinformation.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString HVACPackageBuilder::informationPacket(ServerInformation *f_content)
{
    QJsonObject l_root_obj;
    l_root_obj["header"] = "server_hello";

    QJsonObject l_data;
    l_data["application"] = f_content->app_name;
    l_data["version"] = f_content->app_version.toString();
    l_data["name"] = f_content->name;
    l_data["description"] = f_content->description;
    l_data["playercount"] = f_content->playercount;
    l_data["url"] = f_content->asset_url;

    QJsonArray packages = QJsonArray::fromStringList(f_content->package_ids);
    l_data["packages"] = packages;

    l_root_obj = l_data;

    QJsonDocument l_json_document(l_root_obj);
    return l_json_document.toJson(QJsonDocument::Indented);
}
