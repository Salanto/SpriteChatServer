#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include <QString>

struct ServerInformation;

class PacketBuilder
{
public:
    PacketBuilder() = delete;
    ~PacketBuilder() = delete;

    static QByteArray informationPacket(ServerInformation *f_content);
    static QByteArray notificationPacket(QStringList messages);
};

#endif // PACKETBUILDER_H
