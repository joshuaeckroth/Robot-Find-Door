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

Robot::Robot(QString _name, double _angle, double _posX, double _posY) :
        name(_name)
{    
    robotImage = new RobotImage;

    struct properties p;
    p.angle = _angle;
    p.posX = _posX;
    p.posY = _posY;
    propsQueue.enqueue(p);

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

        struct properties p = propsQueue.back();
        p.posX = new_x;
        p.posY = new_y;
        propsQueue.enqueue(p);

        if (this->collides())
        {
            // Undo the last move:
            new_x -= dist*sin(angle*pi/180)/100;
            new_y += dist*cos(angle*pi/180)/100;
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
    rotAngle = -(rotAngle)+90.0;
    QTimeLine *t = new QTimeLine(2000);
    t->setFrameRange(0, 100);
    QGraphicsItemAnimation *a = new QGraphicsItemAnimation;
    a->setItem((QGraphicsItem*)robotImage);
    a->setTimeLine(t);
    for(int i = 0; i <= 100; i++)
    {
        struct properties p = propsQueue.back();
        p.angle = ((rotAngle - propsQueue.back().angle) * i / 100.0)
                  + propsQueue.back().angle;
        propsQueue.enqueue(p);

        a->setRotationAt(i/100.0, propsQueue.back().angle);

        if (this->collides())
        {
            // Undo the last rotate:
            struct properties p = propsQueue.back();
            p.angle = (-(rotAngle - propsQueue.back().angle) * i / 100.0)
                      + propsQueue.back().angle;
            propsQueue.enqueue(p);
            a->setRotationAt(i/100.0, propsQueue.back().angle);
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

void Robot::setMap(Map *m)
{
    myMap = m;
}

bool Robot::collides()
{
    //test with seed: 5609
    bool detected = false;

    QRectF infoRect = this->getImage()->boundingRect();
    QRectF myRect = QRectF(this->getPosX()-ROBOT_SIZE/2.0, this->getPosY()-ROBOT_SIZE/2.0, infoRect.width(), infoRect.height());
    QList<Obstacle*> Obstacles = myMap->getObstacles();
    for (int i=0;i<Obstacles.size();i++)
    {
        if (  myRect.intersects(Obstacles[i]->boundingRect())  )
        {
            detected = true;
            break;
        }

    }
    return detected;
}
