#include "robotfinddoor.h"
#include <QDebug>

int assignment = 2;

void solution()
{
    Robot *r = getRobot(0);
    r->rotate(180.0);
    r->rotate(90.0);
    r->rotate(270.0);
    r->rotate(0.0);
}
