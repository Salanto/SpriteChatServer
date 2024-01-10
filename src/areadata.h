#ifndef AREADATA_H
#define AREADATA_H

#include <QVector>

class AreaData
{
    struct Background {
        QString name;
        QStringList sides;
    };

    struct Character { //Maybe a bad idea?
        QString name;
        bool taken;
    };

public:
    AreaData(int f_id = -1);
    ~AreaData() {};

    QString getName() const;
    void setName(const QString& f_name);

    QString getBackground() const;
    QStringList getSides() const;
    void setBackground(const QString& f_name, const QStringList& f_sides);


private:
    int id;
    QString name;
    Background background;
};

#endif // AREADATA_H
