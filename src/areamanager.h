#ifndef AREAMANAGER_H
#define AREAMANAGER_H

#include <QObject>

class PacketRelay;
class AreaData;

class AreaManager : public QObject
{
    Q_OBJECT

public:
    explicit AreaManager(QObject *parent = nullptr, PacketRelay* f_relay = nullptr);

private:
    void loadAreasFromFile(const QString &f_filename);

    PacketRelay* relay;
    QVector<AreaData*> areas;
    QVector<int> parent_area;
    QVector<QList<int>> visible_areas;
};

#endif // AREAMANAGER_H
