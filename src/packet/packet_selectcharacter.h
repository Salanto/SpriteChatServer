#ifndef PACKET_SELECTCHARACTER_H
#define PACKET_SELECTCHARACTER_H

#include "packet.h"

class PacketSelectCharacter : public Packet
{
  public:
    PacketSelectCharacter() = default;
    bool fromJsonValue(const QJsonValue &f_in) override;
    QString header() const override;
    QString character() const;

  private:
    QString m_character;
};
#endif // PACKET_SELECTCHARACTER_H
