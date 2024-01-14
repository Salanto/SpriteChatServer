#ifndef AREAMANAGER_H
#define AREAMANAGER_H

#include <QObject>

#include "datatypes.h"

class Area;

class AreaManager : public QObject
{
    class PacketRelay;
    Q_OBJECT

public:
    explicit AreaManager(QObject *parent = nullptr, PacketRelay* f_relay = nullptr);


    bool loadAreaFromFile(const QString& f_file);

private:
    QStringList readCharacters(const QString& f_file);
    Datatypes::BackgroundList readBackground(const QString& f_file);
    Datatypes::MusicList readMusicList(const QString f_file);

    PacketRelay* relay;
    QVector<Area*> areas;
};

#endif // AREAMANAGER_H
