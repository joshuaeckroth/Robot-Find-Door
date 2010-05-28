#include <QString>
#include <QGraphicsItem>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <cmath>

#include "robot.h"
#include "robotimage.h"
#include "solutionrunner.h"

Robot::Robot(QString _name, double _angle, double _posX, double _posY) :
        name(_name), angle(_angle), posX(_posX), posY(_posY)
{    
    robotImage = new RobotImage;

    checkBounds();

    robotImage->setPos(posX, posY);
    QTransform transform;
    transform.rotate(angle);
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

double Robot::moveForward(double dist)
{
    return 0.0;
}

void Robot::rotate(double angle)
{
    QTimeLine *t = new QTimeLine(2000);
    t->setFrameRange(0, 200);
    QGraphicsItemAnimation *a = new QGraphicsItemAnimation;
    a->setItem((QGraphicsItem*)robotImage);
    a->setTimeLine(t);
    for(int i = 0; i < 200; i++)
    {
        a->setRotationAt(i/200.0, angle * i / 200.0);
    }
    emit addTimeLine(t);
}

void Robot::setSolutionRunner(SolutionRunner *s)
{
    solutionRunner = s;
    connect(this, SIGNAL(addTimeLine(QTimeLine*)), solutionRunner, SLOT(addTimeLine(QTimeLine*)));
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
