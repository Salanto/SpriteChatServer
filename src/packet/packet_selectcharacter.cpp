#include "packet_selectcharacter.h"

#include <QJsonObject>

bool PacketSelectCharacter::fromJsonValue(const QJsonValue &f_in)
{
    if (!f_in.isObject()) {
        return false;
    }
    QJsonObject l_data = f_in.toObject();
    m_character = l_data["character"].toString("INVALID");
    return true;
}

QString PacketSelectCharacter::header() const
{
    return "SELECT_CHARACTER";
}

QString PacketSelectCharacter::character() const
{
    return m_character;
}
