#include "packet_hello.h"

bool PacketHello::fromJsonValue(const QJsonValue &f_in)
{
    if (!f_in.isObject()) {
        return false;
    }
    QJsonObject l_data = f_in.toObject();

    application_name = l_data["application"].toString("UNKNOWN");
    version = QVersionNumber::fromString(l_data["version"].toString("0.0.0"));
    identifier = l_data["identifier"].toString("UNKNOWN");

    return true;
}

QString PacketHello::header() const
{
    return "HELLO";
}

QString PacketHello::appName() const
{
    return application_name;
}

QVersionNumber PacketHello::appVersion() const
{
    return version;
}

QString PacketHello::hwid() const
{
    return identifier;
}
