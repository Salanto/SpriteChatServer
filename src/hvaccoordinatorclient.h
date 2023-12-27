#ifndef HVACCOORDINATORCLIENT_H
#define HVACCOORDINATORCLIENT_H

#include <QObject>

struct ServerInformation;
class QNetworkAccessManager;
class QNetworkReply;
class QTimer;

class HVACCoordinatorClient : public QObject
{
    Q_OBJECT
public:
    explicit HVACCoordinatorClient(QObject *parent = nullptr, ServerInformation* f_information = nullptr, bool f_enabled = true, int f_ws_port = -1);
    void setAdvertisementEnabled(bool f_state);

private slots:
    void onAdvertisementTimeout();
    void onCoordinatorReply(QNetworkReply* f_reply);

private:
    ServerInformation* s_information;
    QNetworkAccessManager* ms_client;
    QTimer* timeout;

    int ws_port;

    const int advertisement_timeout = 1000 * 5;
    const QString coordinator_url = "https://servers.aceattorneyonline.com/servers";

};

#endif // HVACCOORDINATORCLIENT_H
