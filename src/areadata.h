#ifndef AREADATA_H
#define AREADATA_H

#include <QVector>

class AreaData
{
public:
    AreaData(int f_root = -1, int f_id = -1, QVector<int> f_visible_areas = {});
    ~AreaData() {};

private:
    int root_id;
    int id;
    QVector<int> visible_areas;
};

#endif // AREADATA_H
