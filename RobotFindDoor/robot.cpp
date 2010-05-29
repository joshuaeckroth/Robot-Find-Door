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
    double pi = 3.14159265;
    // angle is in degrees...
    double angle = this->getAngle();

    QTimeLine *t = new QTimeLine(2000);
    t->setFrameRange(0, 100);
    QGraphicsItemAnimation *a = new QGraphicsItemAnimation;
    a->setItem((QGraphicsItem*)robotImage);
    a->setTimeLine(t);

    double old_x = this->getPosX(), old_y = this->getPosY(),
           new_x = old_x, new_y = old_y;
    for(int i = 0; i <= 100; i++)
    {
        new_x += dist*sin(angle*pi/180)/100;
        new_y -= dist*cos(angle*pi/180)/100;
        a->setPosAt(i/100.0, QPointF(new_x, new_y));
    }

    // update robot's positions inside the class:
    struct properties p = propsQueue.back();
    p.posX = new_x;
    p.posY = new_y;
    propsQueue.enqueue(p);

    timelines.push_back(t);
    animations.push_back(a);

    emit addTimeLine(t);

    return sqrt(pow(new_x-old_x,2.0)+pow(new_y-old_y,2.0));
}

void Robot::rotate(double rotAngle)        
{
    rotAngle = -(rotAngle)+90.0;
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
