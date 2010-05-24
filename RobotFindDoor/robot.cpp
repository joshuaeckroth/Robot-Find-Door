#include <QString>
#include <QGraphicsItem>

#include "robot.h"
#include "robotimage.h"

Robot::Robot(QString _name, double _angle, double _posX, double _posY) :
        name(_name), angle(_angle), posX(_posX), posY(_posY)
{
    robotImage = new RobotImage;
    robotImage->setPos(posX, posY);
    QTransform transform;
    transform.rotate(angle * 180 / 3.141592653589);
    robotImage->setTransform(transform);
}

Robot::~Robot()
{
    delete robotImage;
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

RobotImage *Robot::getImage() const
{
    return robotImage;
}
