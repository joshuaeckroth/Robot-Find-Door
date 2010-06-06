#include "robotfinddoor.h"
#include <QDebug>

#include <cmath>
#include <QtDebug>

extern double ROBOT_SIZE;

int assignment = 2;

void solution()
{    
    Robot *r = getRobot(0);
    Door *d = getDoor(0);

    // Find the door:
    double pi = 3.14159265;
    double x = r->getPosX(), y = r->getPosY();
    double dx = d->getPosX(), dy = d->getPosY();
    double dist = sqrt(pow(x-dx,2.0)+pow(y-dy,2.0));
    double theta = -atan2(dy-y, dx-x) * 180/pi;

    r->rotate(theta);

    bool try_bottom = true;
    // Infinite loops cause the trials to not display at all...
    int trial = 0;
    while (r->moveForward(dist) < dist && trial < 10)
    {
        trial++;
        r->moveForward(-ROBOT_SIZE/2.0);
        if (try_bottom) {
            r->rotate(-90.0);
            r->moveForward(500.0-r->getPosY());
        }
        else {
            r->rotate(90.0);
            r->moveForward(r->getPosY()-ROBOT_SIZE);
        }
        if (r->getPosX() < dx) {
            r->rotate(0.0);
            r->moveForward(500.0-r->getPosX());
        }
        else {
            r->rotate(180.0);
            r->moveForward(r->getPosX()-ROBOT_SIZE);
        }

        x = r->getPosX();
        y = r->getPosY();
        dist = sqrt(pow(x-dx,2.0)+pow(y-dy,2.0));
        theta = -atan2(dy-y, dx-x) * 180/pi;

        r->rotate(theta);
        try_bottom = !try_bottom;
    }
    if (enterDoor(r, d)) qDebug("Success!");
    else qDebug("Whoopsie!");
}
