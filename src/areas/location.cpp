#include "location.h"

#include <QDebug>

Location::Location(QObject *parent) :
    QObject{parent}
{
    qDebug() << "";
}

Location::~Location()
{

}
