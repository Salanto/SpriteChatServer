#ifndef HVACSERVERINFORMATION_H
#define HVACSERVERINFORMATION_H

#include <QString>
#include <QStringList>
#include <QVersionNumber>

struct ServerInformation
{
    QString app_name;
    QVersionNumber app_version;
    QString name;
    QString description;
    int playercount = 0;
    QString asset_url;
    QStringList package_ids;
};

#endif // HVACSERVERINFORMATION_H
