#ifndef SIGNALRELAY_H
#define SIGNALRELAY_H

#include <QObject>

class SignalRelay : public QObject
{
    Q_OBJECT
public:
    explicit SignalRelay(QObject *parent = nullptr);

signals:
};

#endif // SIGNALRELAY_H
