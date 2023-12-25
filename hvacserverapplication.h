#ifndef HVACSERVERAPPLICATION_H
#define HVACSERVERAPPLICATION_H

#include <QCoreApplication>
#include <QVersionNumber>

#include "hvacserverinformation.h"

class HVACConnectionHandler;

class HVACServerApplication : public QCoreApplication
{
    Q_OBJECT
public:
    explicit HVACServerApplication(int argc, char *argv[]);

    void start();
signals:

private:
    HVACConnectionHandler *con_hand;
    ServerInformation information;
};

#endif // HVACSERVERAPPLICATION_H
