#ifndef PACKET_GENERIC_H
#define PACKET_GENERIC_H

#include "abstractpacket.h"

class PacketGeneric : public AbstractPacket
{
public:
    PacketGeneric() = default;
    PacketGeneric(QJsonValue f_data);

    QString header() const override { return "INVALID"; }
    bool fromJsonValue(const QJsonValue &f_data) override
    {
        Q_UNUSED(f_data);
        return true;
    }
};

#endif // PACKET_GENERIC_H
