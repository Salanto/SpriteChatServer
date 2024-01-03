#ifndef CLIENT_H
#define CLIENT_H

#include <QHostAddress>
#include <QObject>

class QWebSocket;

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QObject *parent, QWebSocket *f_socket, int f_id);
    ~Client();

    void write(const QByteArray f_data);
    int id() { return m_id; }

signals:
    void networkDataReceived(const QString &f_data, Client *f_client);
    void socketDisconnected(Client *f_client);

private:
    int m_id;
    QWebSocket *m_socket;
};

#endif // CLIENT_H
