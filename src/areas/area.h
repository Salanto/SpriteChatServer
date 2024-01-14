#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QVector>
#include <QMap>

#include "location.h"
#include "datatypes.h"

/**
 * The common.
 * An area stores the shared information between locations.
 * This content can be modified by commands, but applies to all member locations.
 *
 */

class Area : public QObject
{
    Q_OBJECT
public:
    explicit Area(QObject *parent = nullptr);


    // Unfunny metadata
    void setID(const int f_id);
    int getID() const;
    QStringList getCharacterList() const;
    void setCharacterList(const QStringList& f_characters);
    QStringList getBackgroundList() const;
    void setBackgroundList(Datatypes::BackgroundList &f_backgrounds);
    Datatypes::MusicList getMusicList() const;
    void setMusicList(const Datatypes::MusicList& f_musiclist);

    bool loadLocations(QJsonValue f_locations);

private:
    QVector<Location*> locations; // aka areas in AO2 slang.
    QStringList characters;
    QMap<QString, Datatypes::BackgroundInformation> backgrounds;
    Datatypes::MusicList musiclist;

    int id;

signals:
};

#endif // AREA_H
