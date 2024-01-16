#ifndef PACKETSELECTAREA_H
#define PACKETSELECTAREA_H

#include "packet.h"

class PacketSelectArea : public Packet
{
  public:
    PacketSelectArea() = default;
    bool fromJsonValue(const QJsonValue &f_in) override;
    QString header() const override;
    int getArea() const;
    int getLocation() const;
    void setArea(const int f_area);
    void setLocation(const int f_location);

  private:
    int area;
    int location;
};

#endif // PACKETSELECTAREA_H
