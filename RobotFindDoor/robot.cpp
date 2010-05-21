#include <QString>

#include "robot.h"

Robot::Robot(QString _name, double _angle, double _posX, double _posY) :
        name(_name), angle(_angle), posX(_posX), posY(_posY)
{

}

QString Robot::getName() const
{
    return name;
}

double Robot::getAngle() const
{
    return angle;
}

double Robot::getPosX() const
{
    return posX;
}

double Robot::getPosY() const
{
    return posY;
}
