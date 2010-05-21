#include <cstdlib>

#include <QString>

#include "robot.h"
#include "manager.h"

Robot& newRobot(QString name)
{
    Manager *m = Manager::instance();
    int seed = m->getNextSeed();

    qsrand(seed);

    int rand_max = 0x7FFF;
    double angle = 2.0 * 3.141592653589 * (double)qrand() / rand_max;
    double posX, posY;

    do
    {
        posX = (double)qrand() / rand_max;
        posY = (double)qrand() / rand_max;
    }
    while(m->spaceOccupied(posX, posY));

    Robot *r = new Robot(name, angle, posX, posY);
    m->addRobot(r);
    return *r;
}

double robotForward(Robot &r, double dist)
{
    return 0;
}

void robotRotate(Robot &r, double angle)
{

}

