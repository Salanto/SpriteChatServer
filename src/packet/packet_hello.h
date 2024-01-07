#ifndef PACKET_HELLO_H
#define PACKET_HELLO_H

#include "packet.h"

#include <QVersionNumber>
#include <QJsonObject>

class PacketHello : public Packet
{
public:
    PacketHello() = default;

    bool fromJsonValue(const QJsonValue &f_in) override {
        if (!f_in.isObject()) {
            return false;
        }
        QJsonObject l_data = f_in.toObject();

        application_name = l_data["application"].toString("UNKNOWN");
        version = QVersionNumber::fromString(l_data["version"].toString("0.0.0"));
        identifier = l_data["identifier"].toString("UNKNOWN");

        return true;
    }
    QString header() const override { return "HELLO"; }
    QString app_name() const { return application_name; }
    QVersionNumber app_version() const { return version; }
    QString hwid() const { return identifier; }

private:
    QString application_name;
    QVersionNumber version = {0, 0, 0};
    QString identifier;
};

#endif // PACKET_HELLO_H
