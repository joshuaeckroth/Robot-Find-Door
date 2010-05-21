#include <QString>

#include "robot.h"
#include "robotmanager.h"

Robot& newRobot(QString name)
{
    Robot *r = new Robot(name, 0, 0, 0);
    RobotManager *rm = RobotManager::instance();
    rm->addRobot(r);
    return *r;
}

double robotForward(Robot &r, double dist)
{

}

void robotRotate(Robot &r, double angle)
{

}

