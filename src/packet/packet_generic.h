#ifndef PACKET_GENERIC_H
#define PACKET_GENERIC_H

#include "abstractpacket.h"

class PacketGeneric : public AbstractPacket
{
public:
    PacketGeneric() = default;
    PacketGeneric(QJsonValue f_data);

    QString header() const override { return "INVALID"; }
};

#endif // PACKET_GENERIC_H
