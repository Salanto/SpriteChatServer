#ifndef HVAVCONNECTIONHANDLER_H
#define HVAVCONNECTIONHANDLER_H

#include <QObject>

class QWebSocketServer;
class QWebSocket;
class ServerInformation;

class HVACConnectionHandler : public QObject
{
    Q_OBJECT
public:
    explicit HVACConnectionHandler(QObject *parent = nullptr,
                                   ServerInformation *f_information = nullptr);
    bool start();

signals:
    void socketConnected(QWebSocket *f_socket);

private slots:
    void onWebSocketConnect();

private:
    void sendServerInformation(QWebSocket *f_socket);

    QWebSocketServer *ws_server = nullptr;
    ServerInformation *information;
};

#endif // HVAVCONNECTIONHANDLER_H
