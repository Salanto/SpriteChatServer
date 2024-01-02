#include "packetfactory.h"

bool PacketFactory::canCreatePacket(QString f_header)
{
    return m_builder_map.count(f_header);
}
