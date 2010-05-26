#include <QString>
#include <QGraphicsItem>
#include <cmath>

#include "robot.h"
#include "robotimage.h"

Robot::Robot(QString _name, double _angle, double _posX, double _posY) :
        name(_name), angle(_angle), posX(_posX), posY(_posY)
{    
    robotImage = new RobotImage;

    this->checkBounds();

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

bool Robot::checkBounds() {
    qreal _posX = posX, _posY = posY;

    // Keep the robot within X bounds:
    if (posX > MAP_WIDTH-sqrt(2*(ROBOT_SIZE*ROBOT_SIZE))) posX = MAP_WIDTH-sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));
    else if (posX < sqrt(2*(ROBOT_SIZE*ROBOT_SIZE))) posX = sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));

    // Keep the robot within Y bounds:
    if (posY > MAP_HEIGHT-sqrt(2*(ROBOT_SIZE*ROBOT_SIZE))) posY = MAP_HEIGHT-sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));
    else if (posY < sqrt(2*(ROBOT_SIZE*ROBOT_SIZE))) posY = sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));

    // If (X,Y) was modified, return false.
    if (_posX == posX && _posY == posY) return true;
    else return false;
}
