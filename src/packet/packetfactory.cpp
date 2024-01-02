#include "packetfactory.h"

bool PacketFactory::canCreatePacket(QString f_header)
{
    return m_builder_map.count(f_header);
}

Packet *PacketFactory::createPacket(QString f_header, QJsonDocument f_data)
{
    if (canCreatePacket(f_header)) {
        return new m_builder_map[f_header](f_data);
    }
}


template<class T>
void PacketFactory::registerPacket(QString f_header)
{
    m_builder_map[f_header] = {&createPacket<T>}
}
