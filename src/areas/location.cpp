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

int Location::getID() const
{
    return id;
}

void Location::setID(const int &f_id)
{
    id = f_id;
}

QString Location::getName() const
{
    return name;
}

void Location::setName(const QString &f_name)
{
    name = f_name;
}

QString Location::getDescription() const
{
    return description;
}

void Location::setDescription(const QString &f_description)
{
    if (f_description.isEmpty()) {
        description = "No description provided.";
        return;
    }
    description = f_description;
}

Datatypes::BackgroundInformation Location::getBackground() const
{
    return background;
}

void Location::setBackground(const Datatypes::BackgroundInformation &f_background)
{
    background = f_background;
}
