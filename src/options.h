#ifndef OPTIONS_H
#define OPTIONS_H

#include <QHostAddress>
#include <QSettings>

class Options
{
public:
    //You should NEVER instance this.
    Options() = delete;
    ~Options() = delete;

    static bool filesPresent();
    static void load();
    static void reload();

    static int ws_port();
    static QString server_name();
    static QString server_description();
    static QString hostname();
    static QString asset_url();
    static QHostAddress bind_ip();
    static int max_players();

    static bool advertise();
private:
    inline static QSettings *settings = nullptr;
    inline static const QStringList files{"config/config.ini"};
};

#endif // OPTIONS_H
