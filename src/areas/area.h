#ifndef AREA_H
#define AREA_H

#include <QMap>
#include <QObject>
#include <QVector>

#include "datatypes.h"
#include "location.h"

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
    void setCharacterList(const QStringList &f_characters);
    QStringList getBackgroundList() const;
    void setBackgroundList(const DataTypes::BackgroundList &f_backgrounds);
    DataTypes::MusicList getMusicList() const;
    void setMusicList(const DataTypes::MusicList &f_musiclist);

    bool loadLocations(QJsonValue f_locations);

    Location *getLocationByID(const int id) const;

  private:
    QVector<Location *> locations; // aka areas in AO2 slang.
    QStringList characters;
    QMap<QString, DataTypes::BackgroundInformation> backgrounds;
    DataTypes::MusicList musiclist;

    int id;

  signals:
};

#endif // AREA_H
