#include "robotfinddoor.h"

int assignment = 1;

void solution()
{
    Robot *r = getRobot(0);
    r->rotate(180.0);
    r->rotate(90.0);
    r->rotate(270.0);
}
