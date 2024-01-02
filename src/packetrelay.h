#ifndef PACKETRELAY_H
#define PACKETRELAY_H

#include <QObject>

class Client;

class PacketRelay : public QObject
{
    Q_OBJECT
public:
    explicit PacketRelay(QObject *parent = nullptr);

public slots:
    void packetReceived(QString f_data, Client* f_client);

signals:
    // Sends the packet to a single client.
    void messageSend(const int f_id, const QByteArray f_data);
    // Sends the same packet to multiple clients.
    void multicastSend(const int f_id, const QByteArray f_data);
    // Sends the same packet to all clients.
    void broadcastSend(const QByteArray f_data);
};

#endif // PACKETRELAY_H
