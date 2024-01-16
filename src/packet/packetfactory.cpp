#include "packetfactory.h"
#include "packet_generic.h"
#include "packet_hello.h"
#include "packet_selectcharacter.h"

#include <QJsonDocument>
#include <QJsonParseError>

bool PacketFactory::canCreatePacket(QString f_header)
{
    return m_builder.count(f_header);
}

Packet *PacketFactory::createPacket(QByteArray f_data)
{
    QJsonParseError p_error;
    QJsonDocument l_in = QJsonDocument::fromJson(f_data, &p_error);
    if (p_error.error != QJsonParseError::NoError) {
        return new PacketGeneric();
    }

    QString l_header = l_in["header"].toString().toUpper();
    if (canCreatePacket(l_header)) {
        return m_builder[l_header](l_in["data"]);
    }
    return new PacketGeneric();
}

template <class T>
Packet *PacketFactory::createInstance(QJsonValue f_data)
{
    Packet *l_packet = new T();
    if (!l_packet->fromJsonValue(f_data)) {
        delete l_packet;
        return new PacketGeneric();
    }
    return l_packet;
}

template <typename T>
void PacketFactory::registerPacket(QString header)
{
    QString l_header = T().header();
    Q_ASSERT(!m_builder.count(l_header));
    m_builder[l_header] = &createInstance<T>;
}

void PacketFactory::registerPackets()
{
    registerPacket<PacketHello>("HELLO");
    registerPacket<PacketSelectCharacter>("SELECT_CHARACTER");
}
