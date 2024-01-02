#ifndef ABSTRACTPACKET_H
#define ABSTRACTPACKET_H

#include <type_traits>
#include <QString>
#include <QByteArray>

class AbstractPacket;

template <typename T>
using is_packet = std::enable_if_t<std::is_base_of_v<AbstractPacket, T>, bool>;

class AbstractPacket
{
    virtual ~AbstractPacket();
public:
    virtual QString header() const = 0;
    virtual QByteArray toJson() const = 0;
};

#endif // ABSTRACTPACKET_H
