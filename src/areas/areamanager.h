#ifndef AREAMANAGER_H
#define AREAMANAGER_H

#include <QObject>

class AreaManager : public QObject
{
    class PacketRelay;
    Q_OBJECT

public:
    explicit AreaManager(QObject *parent = nullptr, PacketRelay* f_relay = nullptr);

private:
    PacketRelay* relay;
};

#endif // AREAMANAGER_H
