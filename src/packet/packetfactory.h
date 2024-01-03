#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H

#include "abstractpacket.h"

#include <QString>
#include <map>

using Packet = AbstractPacket;

class PacketFactory
{   
public:
    PacketFactory() = delete;
    ~PacketFactory() = delete;

    bool canCreatePacket(QString f_header);
    Packet *createPacket(QByteArray f_data);
    template<class T, is_packet<T>>
    static void registerPacket(QString header);
    static void registerPackets();

private:
    template<class T>
    static Packet *createInstance(QJsonValue f_data);
    inline static std::map<QString, Packet *(*) (QJsonValue)> m_builder;
};

#endif // PACKETFACTORY_H
