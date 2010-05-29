#include "robotfinddoor.h"
#include <QDebug>

#include <cmath>
#include <QtDebug>

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
    double theta = (atan((y-dy)/(x-dx))-pi/2)*180/pi;

    //17711
    //5411
    //28515 - WTF?
    if (theta < 0) theta += 180;

    qDebug() << "Robot(" << x << ", " << y << ")\nDoor(" << dx << ", " << dy << ")\nAction: " << dist << "@ " << theta << "deg\n";

    r->rotate(theta);
    r->moveForward(dist);   

}
