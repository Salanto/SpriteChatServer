#include "packet_selectarea.h"

#include "QJsonObject"

bool PacketSelectArea::fromJsonValue(const QJsonValue &f_in)
{
    if (!f_in.isObject()) {
        return false;
    }
    QJsonObject l_data = f_in.toObject();
    area = l_data["area"].toInt(0);
    location = l_data["location"].toInt(0);
    return true;
}

QString PacketSelectArea::header() const
{
    return "SELECT_AREA";
}

int PacketSelectArea::getArea() const
{
    return area;
}

int PacketSelectArea::getLocation() const
{
    return location;
}

void PacketSelectArea::setArea(const int f_area)
{
    area = f_area;
}

void PacketSelectArea::setLocation(const int f_location)
{
    location = f_location;
}
