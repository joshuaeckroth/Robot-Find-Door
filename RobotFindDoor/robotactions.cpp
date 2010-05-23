#include <cstdlib>

#include <QString>

#include "robot.h"
#include "manager.h"

Robot& getRobot(int index)
{
    Manager *m = Manager::instance();
    Robot *r = m->getRobot(index);
    return *r;
}

double robotForward(Robot &r, double dist)
{
    return 0;
}

void robotRotate(Robot &r, double angle)
{

}

