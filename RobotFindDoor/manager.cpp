#include "manager.h"
#include "robot.h"

#include <ctime>

Manager* Manager::pInstance = NULL;

Manager* Manager::instance()
{
    if(!pInstance)
        pInstance = new Manager;
    return pInstance;
}

Manager::Manager()
{
    seeds.append(std::time(0));
}

int Manager::getNextSeed()
{
    qsrand(seeds.back());
    seeds.append(qrand());
    return seeds.back();
}

void Manager::addRobot(Robot *r)
{
    robots.append(r);
    emit action(QString("New robot %1 (angle = %2, position = %3, %4)")
                .arg(r->getName()).arg(r->getAngle(), 0, 'f', 2)
                .arg(r->getPosX(), 0, 'f', 2).arg(r->getPosY(), 0, 'f', 2));
}

void Manager::deleteAllRobots()
{
    while(!robots.isEmpty())
        delete robots.takeFirst();
}

bool Manager::spaceOccupied(double posX, double posY)
{
    return false;
}
