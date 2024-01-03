#include "serverapplication.h"
#include "client.h"
#include "clientmanager.h"
#include "coordinatorclient.h"
#include "options.h"
#include "packetrelay.h"

#include <QDebug>

ServerApplication::ServerApplication(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
}

void ServerApplication::start()
{
    qDebug().noquote() << "Starting" << applicationName() << applicationVersion();

    information.app_name = applicationName();
    information.app_version = QVersionNumber::fromString(applicationVersion());
    information.name = Options::server_name();
    information.description = Options::server_description();
    information.asset_url = Options::server_name();
    information.custom_hostname = Options::hostname();

    client_manager = new ClientManager(this, &information);
    advertiser = new CoordinatorClient(this, &information, Options::advertise(), Options::ws_port());
    relay = new PacketRelay(this);
    connect(client_manager, &ClientManager::dataReady, relay, &PacketRelay::packetReceived);
}
