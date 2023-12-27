#include "hvaccoordinatorclient.h"
#include "hvacserverinformation.h"

#include <QNetworkAccessManager>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

HVACCoordinatorClient::HVACCoordinatorClient(QObject *parent, ServerInformation *f_information, bool f_enabled, int f_ws_port) :
    QObject{parent}, s_information{f_information}, ws_port{f_ws_port}
{
    ms_client = new QNetworkAccessManager(this);
    timeout = new QTimer(this);
    timeout->setTimerType(Qt::CoarseTimer);
    timeout->setInterval(advertisement_timeout);
    connect(timeout, &QTimer::timeout, this, &HVACCoordinatorClient::onAdvertisementTimeout);
    connect(ms_client, &QNetworkAccessManager::finished, this, &HVACCoordinatorClient::onCoordinatorReply);

    setAdvertisementEnabled(f_enabled);
}

void HVACCoordinatorClient::setAdvertisementEnabled(bool f_state)
{
    if (f_state) {
        timeout->start();
        qDebug() << "Server advertisement has been enabled.";
    }
    else {
        timeout->stop();
        qDebug() << "Server advertisement has been disabled.";
    }
}

void HVACCoordinatorClient::onAdvertisementTimeout()
{
    QNetworkRequest req;
    req.setUrl(coordinator_url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject l_data_obj;

    if (!s_information->custom_hostname.isEmpty()) {
        l_data_obj["ip"] = s_information->custom_hostname;
    }
    l_data_obj["port"] = 27016;
    l_data_obj["ws_port"] = ws_port;
    l_data_obj["players"] = s_information->playercount;
    l_data_obj["name"] = s_information->name;
    l_data_obj["description"] = s_information->description;

    QJsonDocument l_doc(l_data_obj);
    ms_client->post(req, l_doc.toJson(QJsonDocument::Indented));
}

void HVACCoordinatorClient::onCoordinatorReply(QNetworkReply *f_reply)
{
    if (f_reply->error() != QNetworkReply::NoError) {
        qDebug().noquote() << "Failed to advertise to coordinator. Error:" << f_reply->error();

        QJsonParseError parse_error;
        QJsonObject l_response = QJsonDocument::fromJson(f_reply->readAll(), &parse_error).object();
        if (parse_error.error != QJsonParseError::NoError) {
            qDebug() << "Unable to parse coordinator response. Error:" << parse_error.errorString();
            f_reply->deleteLater();
            return;
        }
        qDebug() << "Error from corrdinator. Error:" << l_response;
    }

    if (f_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        qDebug().noquote() << "Succesfully advertised server.";
    }

    f_reply->deleteLater();
}
