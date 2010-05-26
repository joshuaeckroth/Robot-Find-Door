#include <cstdlib>

#include <QString>

#include "robot.h"
#include "manager.h"

Robot *getRobot(int index)
{
    return Manager::instance()->getRobot(index);
}

double robotForward(Robot *r, double dist)
{
    return 0;
}

void robotRotate(Robot *r, double angle)
{

}

