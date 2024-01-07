#ifndef AREADATA_H
#define AREADATA_H

#include <QVector>

class AreaData
{
public:
    AreaData(int f_root, int f_id, QVector<int> f_visible_areas);
    ~AreaData() {};

private:
    int root_id = -1;
    int id = -1;
    QVector<int> visible_areas = {-1};
};

#endif // AREADATA_H
