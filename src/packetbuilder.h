#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include <QString>

struct ServerInformation;

namespace DataTypes {
    struct BackgroundInformation;
    struct MusicList;
}

// TODO: Merge me with PacketFactory.
// Reason : They are both packet builder classes, just different directions. Merging the factory tho would cause issues and wonky logic.

class PacketBuilder
{
  public:
    PacketBuilder() = delete;
    ~PacketBuilder() = delete;

    static QByteArray informationPacket(ServerInformation *f_content);
    static QByteArray notificationPacket(QStringList messages);
    static QByteArray backgroundPacket(DataTypes::BackgroundInformation *f_content, bool f_reset);
    static QByteArray sidesPacket(DataTypes::BackgroundInformation *f_content);
    static QByteArray musiclistPacket(DataTypes::MusicList *f_content);
    static QByteArray charlistPacket(QStringList f_content);
    static QByteArray arealistPacket(void);
};

#endif // PACKETBUILDER_H
