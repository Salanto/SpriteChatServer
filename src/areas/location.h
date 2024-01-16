#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>

#include "datatypes.h"

/**
 * The unqiue.
 * A location stores meta-data for the clients location on the "virtual map".
 * As such its content can differ between instances
 *
 */

class Location : public QObject
{
  public:
    Location(QObject *parent);
    ~Location();

    int getID() const;
    void setID(const int &f_id);

    QString getName() const;
    void setName(const QString &f_name);

    QString getDescription() const;
    void setDescription(const QString &f_description);

    DataTypes::BackgroundInformation getBackground() const;
    void setBackground(const DataTypes::BackgroundInformation &f_background);

    void removePlayer(int f_player);
    bool joinPlayer(int f_player);

  private:
    int id;
    QString name;
    QString description;
    DataTypes::BackgroundInformation background;
    QString song;
    QList<int> players;
};

#endif // LOCATION_H
