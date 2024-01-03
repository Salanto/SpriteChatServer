#ifndef SERVERINFORMATION_H
#define SERVERINFORMATION_H

#include <QString>
#include <QStringList>
#include <QVersionNumber>

struct ServerInformation
{
    QString app_name;
    QVersionNumber app_version;
    QString name;
    QString description;
    QString custom_hostname;
    int playercount = 0;
    QString asset_url;
    QStringList package_ids;
};

#endif // SERVERINFORMATION_H
