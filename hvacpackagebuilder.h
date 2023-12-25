#ifndef HVACPACKAGEBUILDER_H
#define HVACPACKAGEBUILDER_H

#include <QString>

struct ServerInformation;

class HVACPackageBuilder
{
public:
    HVACPackageBuilder() = delete;
    ~HVACPackageBuilder() = delete;

    static QString informationPacket(ServerInformation *f_content);
};

#endif // HVACPACKAGEBUILDER_H
