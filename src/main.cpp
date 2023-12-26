#include "hvacserverapplication.h"
#include "options.h"

inline static QVersionNumber version = QVersionNumber({0, 0, 1});

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

    return ServerApplication.exec();
}
