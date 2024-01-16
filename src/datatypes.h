#ifndef DATATYPES_H
#define DATATYPES_H

#include <QMap>
#include <QObject>

namespace DataTypes {
Q_NAMESPACE

struct BackgroundInformation
{
    QString name;
    QStringList sides;
    QMap<QString, QString> images;
    QMap<QString, QString> overlays;
};
using BackgroundList = QMap<QString, BackgroundInformation>;

struct MusicCategory
{
    QString category;
    QStringList songs;
};

struct MusicList
{
    QList<MusicCategory> musiclist;
};
};

#endif // DATATYPES_H
