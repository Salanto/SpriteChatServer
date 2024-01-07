#ifndef PACKET_HELLO_H
#define PACKET_HELLO_H

#include "packet.h"

#include <QVersionNumber>
#include <QJsonObject>

class PacketHello : public Packet
{
public:
    PacketHello() = default;

    bool fromJsonValue(const QJsonValue &f_in) override;
    QString header() const override;
    QString appName() const;
    QVersionNumber appVersion() const;
    QString hwid() const;

private:
    QString application_name;
    QVersionNumber version = {0, 0, 0};
    QString identifier;
};

#endif // PACKET_HELLO_H
