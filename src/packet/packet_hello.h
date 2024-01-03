#ifndef PACKET_HELLO_H
#define PACKET_HELLO_H

#include <QJsonDocument>
#include <QVersionNumber>
#include "abstractpacket.h"

class PacketHello : public AbstractPacket
{
public:
    PacketHello();
    PacketHello(QJsonValue f_data);

    QString header() const override { return "HELLO"; }
    bool fromJsonValue(const QJsonValue &f_data) override
    {
        Q_UNUSED(f_data);
        return true;
    }

    QString app_name() const { return application_name; }
    QVersionNumber app_version() const { return version; }
    QString hwid() const { return identifier; }

private:
    QString application_name = "UNKNOWN";
    QVersionNumber version = {0, 0, 0};
    QString identifier = "UNKNOWN";
};

#endif // PACKET_HELLO_H
