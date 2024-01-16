#ifndef AREAMANAGER_H
#define AREAMANAGER_H

#include <QObject>

#include "area.h"
#include "datatypes.h"

class PacketRelay;
class Packet;
class Client;

class AreaManager : public QObject
{
    Q_OBJECT

  public:
    explicit AreaManager(QObject *parent = nullptr, PacketRelay *f_relay = nullptr);

    bool loadAreaFromFile(const QString &f_file);

  private slots:
    void onSelectAreaReceived(Packet *f_packet, Client *f_client);

  private:
    QStringList readCharacters(const QString &f_file);
    DataTypes::BackgroundList readBackgrounds(const QString &f_file);
    DataTypes::MusicList readMusicList(const QString f_file);

    PacketRelay *relay;
    QVector<Area *> areas;
};

#endif // AREAMANAGER_H
