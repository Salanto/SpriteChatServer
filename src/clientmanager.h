#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>

#include "client.h"

struct ServerInformation;
class QWebSocket;
class ConnectionHandler;
class PacketRelay;

class ClientManager : public QObject
{
    Q_OBJECT
    QVector<Client *> clients;
    ConnectionHandler *connection_handler;
    ServerInformation *s_information = nullptr;
    PacketRelay *relay;

  public:
    explicit ClientManager(QObject *parent = nullptr,
                           ServerInformation *f_information = nullptr, PacketRelay *f_relay = nullptr);

  public slots:
    void clientConnected(QWebSocket *f_socket);
    void clientDisconnected(Client *f_client);

    void unicastSend(const int f_id, const QByteArray f_data);
    void multicastSend(const QList<int> f_id, const QByteArray f_data);
    void broadcastSend(const QByteArray f_data);

  signals:
    void dataReady(QByteArray f_data, Client *f_lient);
};

#endif // CLIENTMANAGER_H
