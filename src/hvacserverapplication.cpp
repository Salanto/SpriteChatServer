#include "hvacserverapplication.h"
#include "hvacclientmanager.h"
#include "hvaccoordinatorclient.h"
#include "options.h"

#include <QDebug>

HVACServerApplication::HVACServerApplication(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
}

void HVACServerApplication::start()
{
    qDebug().noquote() << "Starting" << applicationName() << applicationVersion();

    information.app_name = applicationName();
    information.app_version = QVersionNumber::fromString(applicationVersion());
    information.name = Options::server_name();
    information.description = Options::server_description();
    information.asset_url = Options::server_name();
    information.custom_hostname = Options::hostname();

    client_manager = new HVACClientManager(this, &information);
    advertiser = new HVACCoordinatorClient(this, &information, Options::advertise(), Options::ws_port());
}
