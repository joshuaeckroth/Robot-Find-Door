#include "manager.h"
#include "robot.h"
#include "viewport.h"
#include "mapsimple.h"
#include "mapverticalbar.h"

Manager* Manager::pInstance = NULL;

Manager* Manager::instance()
{
    if(!pInstance)
        pInstance = new Manager;
    return pInstance;
}

Manager::Manager() :
        curSeed(-1), map(NULL), viewport(NULL)
{ }

int Manager::getSeed() const
{
    return seeds.back();
}

bool Manager::hasPrevSeed() const
{
    return curSeed != 0;
}

void Manager::setViewport(Viewport *v)
{
    viewport = v;
}

void Manager::initialize()
{
    extern int assignment;
    switch(assignment)
    {
    case 1:
        map = (Map*)(new MapSimple(getSeed()));
        break;
    case 2:
        map = (Map*)(new MapVerticalBar(getSeed()));
        break;
    default:
        return;
    }

    qsrand(seeds[curSeed]);
    map->generate();

    if(viewport)
        viewport->setScene(map);
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

void Manager::setSeed(int seed)
{
    seeds.append(seed);
    curSeed++;
    emit action(QString("New seed: %1").arg(seeds[curSeed]));
    emit newSeed(seeds[curSeed]);
}

void Manager::prevMap()
{
    if(curSeed > 0)
        curSeed--;
    emit action(QString("New seed: %1").arg(seeds[curSeed]));
    emit newSeed(seeds[curSeed]);
}

void Manager::nextMap()
{
    if(curSeed < seeds.size() - 1)
        curSeed++;
    else
    {
        seeds.append(qrand() % 1000); // seeds are 0-999
        curSeed++;
    }
    emit action(QString("New seed: %1").arg(seeds[curSeed]));
    emit newSeed(seeds[curSeed]);
    deleteAllRobots();
    initialize();
}

void Manager::go()
{
    qsrand(seeds[curSeed]);

    emit action(QString("Go!"));

    void solution();
    solution();
}
