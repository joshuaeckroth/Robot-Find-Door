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

double robotForward(double dist)
{
    return robotForward(Manager::instance()->getRobot(0), dist);
}

void robotRotate(Robot *r, double angle)
{

}

void robotRotate(double angle)
{
    robotRotate(Manager::instance()->getRobot(0), angle);
}

