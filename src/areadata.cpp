#include "areadata.h"

#include <QDebug>

AreaData::AreaData(int f_root, int f_id, QVector<int> f_visible_areas) :
    root_id{f_root},
    id{f_id},
    visible_areas{f_visible_areas}
{
    qDebug() << QString("[AREA %1] Creating area with root node %2").arg(QString::number(id), QString::number(root_id));
}
