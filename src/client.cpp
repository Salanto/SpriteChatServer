#include "client.h"

#include <QWebSocket>

Client::Client(QObject *parent, QWebSocket *f_socket, int f_id) :
    QObject{parent},
    m_id{f_id},
    m_socket{f_socket}
{
    connect(m_socket, &QWebSocket::binaryMessageReceived, this, [this](const QByteArray &f_data) {
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
    m_socket->sendBinaryMessage(f_data);
}
