#ifndef HVACCLIENTMANAGER_H
#define HVACCLIENTMANAGER_H

#include <QObject>

struct ServerInformation;
class QWebSocket;
class Client;
class HVACConnectionHandler;

class HVACClientManager : public QObject
{
    Q_OBJECT
    QVector<Client *> clients;
    HVACConnectionHandler *connection_handler;
    ServerInformation *s_information = nullptr;

public:
    explicit HVACClientManager(QObject *parent = nullptr,
                               ServerInformation *f_information = nullptr);

public slots:
    void clientConnected(QWebSocket *f_socket);
    void clientDisconnected(Client *f_client);

signals:
    void dataReady(QString f_data, Client *f_lient);
};

#endif // HVACCLIENTMANAGER_H
