#ifndef PACKET_GENERIC_H
#define PACKET_GENERIC_H

#include "packet.h"

class PacketGeneric : public Packet
{
public:
    PacketGeneric() = default;

    bool fromJsonValue(const QJsonValue &f_in) override {
        Q_UNUSED(f_in);
        return false;
    };
    QString header() const override { return "INVALID"; }
};

#endif // PACKET_GENERIC_H
