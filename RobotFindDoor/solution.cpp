#include "robotfinddoor.h"
#include <QDebug>

int assignment = 2;

void solution()
{
    Robot *r = getRobot(0);   
    r->rotate(0.0);
    r->moveForward(20.0);
    r->rotate(-45.0);
    r->moveForward(20.0);
    r->rotate(-90.0-45.0);
    r->moveForward(20.0);
    r->rotate(180.0);
    r->moveForward(20.0);
}
