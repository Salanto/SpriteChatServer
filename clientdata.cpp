#include "clientdata.h"

#include <QWebSocket>

ClientData::ClientData(QObject *parent, QWebSocket *f_socket, int f_id)
    : QObject{parent}
    , m_socket{f_socket}
    , m_id{f_id}
{
    connect(m_socket, &QWebSocket::textMessageReceived, this, [this](const QString &f_data) {
        // This is essentially a QSignalMapper, but easier to understand.
        emit networkDataReceived(f_data, this);
    });
}

ClientData::~ClientData() {}
