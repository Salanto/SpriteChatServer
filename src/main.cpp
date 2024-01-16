#include "options.h"
#include "serverapplication.h"

inline static QVersionNumber version = QVersionNumber({0, 1, 2});

int main(int argc, char *argv[])
{
    if (!Options::filesPresent()) {
        std::exit(1);
    }
    Options::load();

    ServerApplication ServerApplication(argc, argv);
    ServerApplication.setApplicationName("HVAC-Server");
    ServerApplication.setApplicationVersion(version.toString());
    ServerApplication.start();

    return ServerApplication.exec();
}
