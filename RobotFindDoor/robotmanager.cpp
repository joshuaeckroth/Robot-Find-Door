#include "robotmanager.h"
#include "robot.h"

RobotManager* RobotManager::pInstance = NULL;

RobotManager* RobotManager::instance()
{
    if(!pInstance)
        pInstance = new RobotManager;
    return pInstance;
}

void RobotManager::addRobot(Robot *r)
{
    robots.append(r);
}

void RobotManager::deleteAllRobots()
{
    while(!robots.isEmpty())
        delete robots.takeFirst();
}
