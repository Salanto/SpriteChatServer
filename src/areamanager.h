#ifndef AREAMANAGER_H
#define AREAMANAGER_H

#include <QObject>

class PacketRelay;

class AreaManager : public QObject
{
    Q_OBJECT
public:
    explicit AreaManager(QObject *parent = nullptr, PacketRelay* f_relay = nullptr);

signals:


private:
    PacketRelay* relay;
};

#endif // AREAMANAGER_H
