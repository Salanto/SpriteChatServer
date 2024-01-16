#ifndef BANMANAGER_H
#define BANMANAGER_H

#include <QObject>

class PacketRelay;
class Packet;
class Client;

class BanManager : public QObject
{
    Q_OBJECT

  public:
    explicit BanManager(QObject *parent = nullptr, PacketRelay *f_relay = nullptr);

  private slots:
    void onHELLOReceived(Packet *f_packet, Client *f_client);

  public:
    PacketRelay *relay;
};

#endif // BANMANAGER_H
