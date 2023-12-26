#ifndef HVACCLIENTMANAGER_H
#define HVACCLIENTMANAGER_H

#include <QObject>

struct ServerInformation;
class QWebSocket;
class ClientData;
class HVACConnectionHandler;

class HVACClientManager : public QObject
{
    Q_OBJECT
    QVector<ClientData *> clients;
    HVACConnectionHandler *connection_handler;
    ServerInformation *s_information = nullptr;

public:
    explicit HVACClientManager(QObject *parent = nullptr,
                               ServerInformation *f_information = nullptr);

public slots:
    void clientConnected(QWebSocket *f_socket);
    void clientDisconnected();

signals:
    void dataReady(QString f_data, ClientData *f_lient);
};

#endif // HVACCLIENTMANAGER_H
