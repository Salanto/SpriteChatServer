#include "options.h"

#include <QDebug>
#include <QFile>

bool Options::filesPresent()
{
    bool file_present = true;
    for (const QString &file : files) {
        if (!QFile::exists(file)) {
            qDebug().noquote() << "Missing configuration file at" << file;
            file_present = false;
        }
    }
    return file_present;
}

void Options::load()
{
    Options::settings = new QSettings("./config/config.ini", QSettings::IniFormat, nullptr);
}

void Options::reload()
{
    Options::settings->sync();
    Options::settings->deleteLater();
    load();
}

int Options::ws_port()
{
    return settings->value("server/ws_port", 50001).toInt();
}

QString Options::server_name()
{
    return settings->value("server/name", "An unnamed Server").toString();
}

QString Options::server_description()
{
    return settings->value("server/description", "No description provided.").toString();
}

QString Options::hostname()
{
    return settings->value("coordinator/hostname", "").toString();
}

bool Options::advertise()
{
    return settings->value("coordinator/advertise", false).toBool();
}

QStringList Options::areas()
{
    return settings->value("map/areas", {"default"}).toStringList();
}

QString Options::asset_url()
{
    return settings->value("assets/url", "").toString();
}

QHostAddress Options::bind_ip()
{
    QString l_bind = settings->value("server/bind_ip", "").toString();
    if (l_bind.isEmpty()) {
        return QHostAddress::Any;
    }
    return QHostAddress(l_bind);
}

int Options::max_players()
{
    return settings->value("server/max_players", 100).toInt();
}
