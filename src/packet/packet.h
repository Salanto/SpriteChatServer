#ifndef PACKET_H
#define PACKET_H

#include <QJsonValue>
#include <QString>

class Packet
{
public:
    virtual ~Packet() = default;
    virtual bool fromJsonValue(const QJsonValue &f_in) = 0;
    virtual QString header() const = 0;
};

#endif // PACKET_H
