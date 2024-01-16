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

    bool const l_is_local = (f_socket->peerAddress() == QHostAddress::LocalHost) ||
                            (f_socket->peerAddress() == QHostAddress::LocalHostIPv6) ||
                            (f_socket->peerAddress() == QHostAddress("::ffff:127.0.0.1"));
    // TLDR : We check if the header comes trough a proxy/tunnel running locally.
    // This is to ensure nobody can send those headers from the web.
    QNetworkRequest l_request = f_socket->request();
    if (l_request.hasRawHeader("x-forwarded-for") && l_is_local) {
        socket_ip = QHostAddress(QString::fromUtf8(l_request.rawHeader("x-forwarded-for")));
    }
    else {
        socket_ip = f_socket->peerAddress();
    }
}

Client::~Client()
{
    m_socket->deleteLater();
}

void Client::write(const QByteArray f_data)
{
    m_socket->sendBinaryMessage(f_data);
}

QHostAddress Client::getIP() const
{
    return socket_ip;
}
