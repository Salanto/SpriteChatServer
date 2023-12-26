#ifndef CLIENT_H
#define CLIENT_H

#include <QHostAddress>
#include <QObject>

class QWebSocket;

class ClientData : public QObject
{
    Q_OBJECT

public:
    ClientData(QWebSocket *f_socket, int f_id);
    ~ClientData();

signals:
    void clientDataReceived(const QString &f_data, ClientData *f_client);

private:
    int m_id;
    QWebSocket *m_socket;
};

#endif // CLIENT_H
