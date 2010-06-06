#include <QString>
#include <QGraphicsItem>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QDebug>
#include <cmath>

#include "map.h"
#include "robot.h"
#include "robotimage.h"
#include "solutionrunner.h"

Robot::Robot(QString _name, double _angle, double _posX, double _posY, Map *_map) :
        name(_name), map(_map)
{    
    robotImage = new RobotImage;

    struct properties p;
    p.angle = _angle;
    p.posX = _posX;
    p.posY = _posY;
    propsQueue.enqueue(p);

    robotImage->setPos(_posX, _posY);
    QTransform transform;
    transform.rotate(-_angle);
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
    double angle = getAngle();

    RobotImage tmpImage = RobotImage(*robotImage);

    QTimeLine *t = new QTimeLine(2000);
    t->setFrameRange(0, 100);
    QGraphicsItemAnimation *a = new QGraphicsItemAnimation;
    a->setItem((QGraphicsItem*)robotImage);
    a->setTimeLine(t);

    double old_x = getPosX(), old_y = getPosY(),
           new_x = old_x, new_y = old_y;
    for(int i = 0; i <= 100; i++)
    {
        new_x += dist*cos(angle*pi/180)/100;
        new_y -= dist*sin(angle*pi/180)/100;
        a->setPosAt(i/100.0, QPointF(new_x, new_y));
        tmpImage.setPos(QPointF(new_x, new_y));

        struct properties p = propsQueue.back();
        p.posX = new_x;
        p.posY = new_y;
        propsQueue.enqueue(p);

        if (map->collides(&tmpImage, true))
        {
            // Undo the last move:
            new_x -= dist*cos(angle*pi/180)/100;
            new_y += dist*sin(angle*pi/180)/100;
            a->setPosAt(i/100.0, QPointF(new_x, new_y));
            struct properties p = propsQueue.back();
            p.posX = new_x;
            p.posY = new_y;
            propsQueue.enqueue(p);
            // Quit:
            break;
        }
    }

    timelines.push_back(t);
    animations.push_back(a);

    emit addTimeLine(t);

    return sqrt(pow(new_x-old_x,2.0)+pow(new_y-old_y,2.0));
}

void Robot::rotate(double rotAngle)        
{
    RobotImage tmpImage = RobotImage(*robotImage);

    // don't spin around more than a complete circle
    if(rotAngle < 0.0) rotAngle += 360.0;

    QTimeLine *t = new QTimeLine(2000);
    t->setFrameRange(0, 100);
    QGraphicsItemAnimation *a = new QGraphicsItemAnimation;
    a->setItem((QGraphicsItem*)robotImage);
    a->setTimeLine(t);
    for(int i = 0; i <= 100; i++)
    {
        struct properties p = propsQueue.back();
        p.angle = -(-propsQueue.back().angle -
                    ((-propsQueue.back().angle + rotAngle) * i / 100.0));
        propsQueue.enqueue(p);

        a->setRotationAt(i/100.0, -propsQueue.back().angle);

        QTransform t = tmpImage.transform();
        t.rotate(-propsQueue.back().angle);
        tmpImage.setTransform(t);

        if (map->collides(&tmpImage, true))
        {
            // Undo the last rotate:
            struct properties p = propsQueue.back();
            p.angle = -(-propsQueue.back().angle +
                        ((-propsQueue.back().angle + rotAngle) * i / 100.0));
            propsQueue.enqueue(p);
            a->setRotationAt(i/100.0, -propsQueue.back().angle);
            // Quit:
            break;
        }
    }

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
