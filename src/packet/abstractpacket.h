#ifndef ABSTRACTPACKET_H
#define ABSTRACTPACKET_H

#include <QJsonValue>
#include <QString>
#include <type_traits>

class AbstractPacket;

template<typename T>
using is_packet
    = std::enable_if_t<std::is_base_of_v<AbstractPacket, T> && std::is_default_constructible_v<T>,
                       bool>;

class AbstractPacket
{
public:
    virtual QString header() const = 0;
    virtual bool fromJsonValue(const QJsonValue &f_data) = 0;
};

#endif // ABSTRACTPACKET_H
