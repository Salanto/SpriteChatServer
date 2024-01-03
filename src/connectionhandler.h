#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QHostAddress>
#include <QObject>

class QWebSocketServer;
class QWebSocket;
class ServerInformation;

class ConnectionHandler : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionHandler(QObject *parent = nullptr,
                                   ServerInformation *f_information = nullptr);
    bool start(QHostAddress f_bind, int f_ws_port);

signals:
    void gameSocketConnected(QWebSocket *f_socket);
    void probeSocketConnected(QWebSocket *f_socket);

private slots:
    void onSocketConnect();
    void sendServerInformation(QWebSocket *f_socket);

private:
    using Route = void (ConnectionHandler::*)(QWebSocket *);
    std::map<QString, Route> routes;

    QWebSocketServer *ws_server = nullptr;
    ServerInformation *information;
};

#endif // CONNECTIONHANDLER_H
