#ifndef PACKETRELAY_H
#define PACKETRELAY_H

#include <QObject>
#include <QString>
#include <map>

class Client;
class AbstractPacket;

class PacketRelay : public QObject
{
    Q_OBJECT
    using Packet = AbstractPacket;
public:
    explicit PacketRelay(QObject *parent = nullptr);

public slots:
    void packetReceived(QByteArray f_data, Client *f_client);

signals:
    // Sends the packet to a single client.
    void unicastSend(const int f_id, const QByteArray f_data);
    // Sends the same packet to multiple clients.
    void multicastSend(const int f_id, const QByteArray f_data);
    // Sends the same packet to all clients.
    void broadcastSend(const QByteArray f_data);


    void softwareInformation(Packet* f_data, Client* f_client);

private:
    bool canRoutePacket(QString f_header);
    using Route = void (PacketRelay::*)(Packet *, Client *);
    std::map<QString, Route> routes;
};

#endif // PACKETRELAY_H
