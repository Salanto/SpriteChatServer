#include "areadata.h"

#include <QDebug>

AreaData::AreaData(int f_id) :
    id{f_id}
{
    qDebug() << QString("[AREA %1] Created").arg(QString::number(id));
}

QString AreaData::getName() const
{
    return name;
}

void AreaData::setName(const QString &f_name)
{
    name = f_name;
}

QString AreaData::getBackground() const
{
    return background.name;
}

QStringList AreaData::getSides() const
{
    return background.sides;
}

void AreaData::setBackground(const QString &f_name, const QStringList &f_sides)
{
    background.name = f_name;
    background.sides = f_sides;
}
