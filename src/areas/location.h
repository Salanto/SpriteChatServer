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
    Location(QObject* parent);
    ~Location();

    int getID() const;
    void setID(const int& f_id);

    QString getName() const;
    void setName(const QString& f_name);

    QString getDescription() const;
    void setDescription(const QString& f_description);

    Datatypes::BackgroundInformation getBackground() const;
    void setBackground(const Datatypes::BackgroundInformation& f_background);

private:
    int id;
    QString name;
    QString description;
    Datatypes::BackgroundInformation background;
    QString song;
};

#endif // LOCATION_H
