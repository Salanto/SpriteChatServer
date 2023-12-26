#ifndef HVACPACKETBUILDER_H
#define HVACPACKETBUILDER_H

#include <QString>

struct ServerInformation;

class HVACPacketBuilder
{
public:
    HVACPacketBuilder() = delete;
    ~HVACPacketBuilder() = delete;

    static QByteArray informationPacket(ServerInformation *f_content);
};

#endif // HVACPACKETBUILDER_H
