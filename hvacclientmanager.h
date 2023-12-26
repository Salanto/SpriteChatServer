#ifndef HVACCLIENTMANAGER_H
#define HVACCLIENTMANAGER_H

#include <QObject>

class HVACClientManager : public QObject
{
    Q_OBJECT
public:
    explicit HVACClientManager(QObject *parent = nullptr);

signals:
};

#endif // HVACCLIENTMANAGER_H
