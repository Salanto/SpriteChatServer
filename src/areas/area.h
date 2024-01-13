#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QList>

#include "location.h"

class Area : public QObject
{
    Q_OBJECT
public:
    explicit Area(QObject *parent = nullptr);

private:
    QVector<Location> locations;
    QList

signals:
};

#endif // AREA_H
