#include "Client.h"

#include <QWebSocket>

Client::Client(QObject *parent, QWebSocket *f_socket, int f_id)
    : QObject{parent}
    , m_socket{f_socket}
    , m_id{f_id}
{
    connect(m_socket, &QWebSocket::textMessageReceived, this, [this](const QString &f_data) {
        // This is essentially a QSignalMapper, but easier to understand.
        emit networkDataReceived(f_data, this);
    });
    connect(m_socket, &QWebSocket::disconnected, this, [this]() {
        // Clientmanager will handle cleanup.
        emit socketDisconnected(this);
    });
}

Client::~Client()
{
    m_socket->deleteLater();
}

void Client::write(const QByteArray f_data)
{
    m_socket->sendTextMessage(f_data);
}
