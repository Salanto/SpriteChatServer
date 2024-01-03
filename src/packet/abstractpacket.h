#ifndef ABSTRACTPACKET_H
#define ABSTRACTPACKET_H

#include <QJsonValue>
#include <QString>

class AbstractPacket
{
public:
    virtual QString header() const = 0;
};

#endif // ABSTRACTPACKET_H
