#include "manageractions.h"
#include "robot.h"
#include "door.h"
#include <QString>
#include <cmath>
#include <QDebug>

extern double ROBOT_SIZE;

bool enterDoor(Robot *r, Door *d)
{
    QString side = d->getSide();
    double doorX = d->getPosX(),
           doorY = d->getPosY();
    if (side == "RIGHT") {
        r->rotate(0.0);
        doorX += ROBOT_SIZE;
    }
    else if (side == "TOP") {
        r->rotate(90.0);
        doorY -= ROBOT_SIZE;
    }
    else if (side == "LEFT") {
        r->rotate(180.0);
        doorX -= ROBOT_SIZE;
    }
    else {
        r->rotate(270.0);
        doorY += ROBOT_SIZE;
    }
    r->moveForward(ROBOT_SIZE*9/10);

    double threshold = ROBOT_SIZE/5.0;

    qDebug() << "Distance from door:" << sqrt(pow(r->getPosX()-doorX,2.0)+pow(r->getPosY()-doorY,2.0)) << "<" << threshold;
    if (sqrt(pow(r->getPosX()-doorX,2.0)+pow(r->getPosY()-doorY,2.0)) <= threshold) return true;
    else return false;
}
