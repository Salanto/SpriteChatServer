#ifndef SERVERAPPLICATION_H
#define SERVERAPPLICATION_H

#include <QCoreApplication>
#include <QVersionNumber>

#include "serverinformation.h"

class ConnectionHandler;
class ClientManager;
class CoordinatorClient;
class PacketRelay;
class AreaManager;
class BanManager;

class ServerApplication : public QCoreApplication
{
    Q_OBJECT

  public:
    explicit ServerApplication(int argc, char *argv[]);

    void start();
  signals:

  private:
    ClientManager *client_manager;
    CoordinatorClient *advertiser;
    ServerInformation information;
    PacketRelay *relay;
    AreaManager *area_manager;
    BanManager *ban_manager;
};

#endif // SERVERAPPLICATION_H
