#ifndef HVACSERVERAPPLICATION_H
#define HVACSERVERAPPLICATION_H

#include <QCoreApplication>
#include <QVersionNumber>

#include "hvacserverinformation.h"

class HVACConnectionHandler;
class HVACClientManager;

class HVACServerApplication : public QCoreApplication
{
    Q_OBJECT
public:
    explicit HVACServerApplication(int argc, char *argv[]);

    void start();
signals:

private:
    HVACClientManager *client_manager;
    ServerInformation information;
};

#endif // HVACSERVERAPPLICATION_H
