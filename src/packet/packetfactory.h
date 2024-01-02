#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H

#include <QString>
#include <QJsonDocument>
#include <map>

class Packet;

class PacketFactory
{   
public:
    PacketFactory() = delete;
    ~PacketFactory() = delete;

    static bool canCreatePacket(QString f_header);
    static Packet *createPacket(QString f_header, QJsonDocument f_data);
    static void registerPackets();

private:
    template<class T>
    static void registerPacket(QString f_header);
    inline static std::map<QString, Packet *(*) (QJsonDocument)> m_builder_map;
};

#endif // PACKETFACTORY_H
