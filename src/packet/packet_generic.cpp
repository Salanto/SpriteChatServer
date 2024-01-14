#include "packet_generic.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

bool PacketGeneric::fromJsonValue(const QJsonValue &f_in)
{
    Q_UNUSED(f_in);
    qDebug() << "ERROR: Cannot populate generic packet.";
    qDebug() << "Packet is either unimplemented, or is meant to be sent to client";
    return false;
}

QString PacketGeneric::header() const
{
    return m_header;
}

QByteArray PacketGeneric::toJsonString() const
{
    QJsonObject l_data;
    l_data["header"] = m_header;
    l_data["data"] = m_data;

    return QJsonDocument(l_data).toJson(QJsonDocument::Compact);
}
