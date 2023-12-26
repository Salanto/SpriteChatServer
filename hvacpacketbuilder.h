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
    static QByteArray notificationPacket(QStringList messages);
};

#endif // HVACPACKETBUILDER_H
