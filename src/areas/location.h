#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>

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
};

#endif // LOCATION_H
