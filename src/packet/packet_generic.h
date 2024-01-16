#ifndef PACKET_GENERIC_H
#define PACKET_GENERIC_H

#include "packet.h"

class PacketGeneric : public Packet
{
  public:
    PacketGeneric() = default;

    bool fromJsonValue(const QJsonValue &f_in) override;
    QString header() const override;
    QString setHeader(const QString f_header);
    QByteArray toJsonString() const;

  private:
    QString m_header;
    QJsonValue m_data;
};

#endif // PACKET_GENERIC_H
