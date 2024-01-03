#ifndef HVACSERVERAPPLICATION_H
#define HVACSERVERAPPLICATION_H

#include <QCoreApplication>
#include <QVersionNumber>

#include "hvacserverinformation.h"

class HVACConnectionHandler;
class HVACClientManager;
class HVACCoordinatorClient;
class PacketRelay;

class HVACServerApplication : public QCoreApplication
{
    Q_OBJECT
public:
    explicit HVACServerApplication(int argc, char *argv[]);

    void start();
signals:

private:
    HVACClientManager *client_manager;
    HVACCoordinatorClient* advertiser;
    ServerInformation information;
    PacketRelay *relay;
};

#endif // HVACSERVERAPPLICATION_H
