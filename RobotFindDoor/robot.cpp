#include <QString>
#include <QGraphicsItem>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QDebug>
#include <cmath>

#include "robot.h"
#include "robotimage.h"
#include "solutionrunner.h"

Robot::Robot(QString _name, double _angle, double _posX, double _posY) :
        name(_name)
{    
    robotImage = new RobotImage;

    struct properties p;
    p.angle = _angle;
    p.posX = _posX;
    p.posY = _posY;
    propsQueue.enqueue(p);

    //checkBounds();

    robotImage->setPos(_posX, _posY);
    QTransform transform;
    transform.rotate(_angle);
    robotImage->setTransform(transform);
}

Robot::~Robot()
{
    delete robotImage;
    while(!timelines.isEmpty())
    {
        delete timelines.last();
        timelines.pop_back();
    }
    while(!animations.isEmpty())
    {
        delete animations.last();
        animations.pop_back();
    }
}

QString Robot::getName() const
{
    return name;
}

double Robot::getAngle() const
{
    return propsQueue.back().angle;
}

double Robot::getPosX() const
{
    return propsQueue.back().posX;
}

double Robot::getPosY() const
{
    return propsQueue.back().posY;
}

RobotImage *Robot::getImage()
{
    return robotImage;
}

double Robot::moveForward(double dist)
{
    return 0.0;
}

void Robot::rotate(double rotAngle)
{
    QTimeLine *t = new QTimeLine(2000);
    t->setFrameRange(0, 100);
    QGraphicsItemAnimation *a = new QGraphicsItemAnimation;
    a->setItem((QGraphicsItem*)robotImage);
    a->setTimeLine(t);
    for(int i = 0; i <= 100; i++)
    {
        a->setRotationAt(i/100.0, ((rotAngle - propsQueue.back().angle) * i / 100.0)
                         + propsQueue.back().angle);
    }

    struct properties p = propsQueue.back();
    p.angle = rotAngle;
    propsQueue.enqueue(p);

    timelines.push_back(t);
    animations.push_back(a);

    emit addTimeLine(t);
}

void Robot::setSolutionRunner(SolutionRunner *s)
{
    solutionRunner = s;
    connect(this, SIGNAL(addTimeLine(QTimeLine*)), solutionRunner, SLOT(addTimeLine(QTimeLine*)));
    connect(solutionRunner, SIGNAL(animationComplete()), this, SLOT(animationComplete()));
}

void Robot::animationComplete()
{
    propsQueue.dequeue();
}

bool Robot::checkBounds() {
    qreal _posX = propsQueue.back().posX, _posY = propsQueue.back().posY;
    qreal posX = _posX, posY = _posY;

    // Keep the robot within X bounds:
    if (posX > MAP_WIDTH-sqrt(2*(ROBOT_SIZE*ROBOT_SIZE)))
        posX = MAP_WIDTH-sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));
    else if (posX < sqrt(2*(ROBOT_SIZE*ROBOT_SIZE))) posX = sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));

    // Keep the robot within Y bounds:
    if (posY > MAP_HEIGHT-sqrt(2*(ROBOT_SIZE*ROBOT_SIZE))) posY = MAP_HEIGHT-sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));
    else if (posY < sqrt(2*(ROBOT_SIZE*ROBOT_SIZE))) posY = sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));

    struct properties p = propsQueue.dequeue();
    p.posX = posX;
    p.posY = posY;
    propsQueue.enqueue(p);

    // If (X,Y) was modified, return false.
    if (_posX == posX && _posY == posY) return true;
    else return false;
}
