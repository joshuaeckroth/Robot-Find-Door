#include "door.h"

#include <QString>

Door::Door(QString _name, double _posX, double _posY) :
        name(_name), posX(_posX), posY(_posY)
{ }

QString Door::getName() const
{
    return name;
}

double Door::getPosX() const
{
    return posX;
}

double Door::getPosY() const
{
    return posY;
}

