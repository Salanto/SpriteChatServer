#include "hvacserverapplication.h"
#include "options.h"

#include "packetrelay.h"

inline static QVersionNumber version = QVersionNumber({0, 0, 2});

int main(int argc, char *argv[])
{
    if (!Options::filesPresent()) {
        std::exit(1);
    }
    Options::load();

    HVACServerApplication ServerApplication(argc, argv);
    ServerApplication.setApplicationName("HVACServer");
    ServerApplication.setApplicationVersion(version.toString());

    ServerApplication.start();

    PacketRelay f_relay;

    return ServerApplication.exec();
}
