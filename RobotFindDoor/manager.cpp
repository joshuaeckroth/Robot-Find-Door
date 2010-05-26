#include "manager.h"
#include "robot.h"
#include "door.h"
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
        curSeed(-1), map(NULL), viewport(NULL), isSolutionComplete(true)
{ }

int Manager::getSeed() const
{
    return seeds.back();
}

bool Manager::hasPrevSeed() const
{
    return curSeed != 0;
}

int Manager::getCurSeed() const
{
    return curSeed;
}

int Manager::getNumSeeds() const
{
    return seeds.size();
}

void Manager::setViewport(Viewport *v)
{
    viewport = v;
}

void Manager::initialize()
{
    deleteAllRobots();
    deleteAllDoors();

    Map *oldMap = map;

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
    // for some reason, several initial calls help obtain greater randomness
    for(int i = 0; i < 20; i++)
        qrand();

    map->generate();

    if(viewport)
        viewport->setMap(map);

    if(oldMap)
        delete oldMap;

    isSolutionComplete = false;
}

void Manager::addRobot(Robot *r)
{
    robots.append(r);
    emit action(QString("New robot %1 (angle = %2, position = %3, %4)")
                .arg(r->getName()).arg(r->getAngle(), 0, 'f', 2)
                .arg(r->getPosX(), 0, 'f', 2).arg(r->getPosY(), 0, 'f', 2));
}

void Manager::addDoor(Door *d)
{
    doors.append(d);
}

void Manager::deleteAllRobots()
{
    while(!robots.isEmpty())
        delete robots.takeFirst();
}

Robot* Manager::getRobot(int index)
{
    if(index < robots.size())
        return robots[index];

    return NULL;
}

void Manager::deleteAllDoors()
{
    while(!doors.isEmpty())
        delete doors.takeFirst();
}

Door* Manager::getDoor(int index)
{
    if(index < doors.size())
        return doors[index];

    return NULL;
}

bool Manager::spaceOccupied(double posX, double posY)
{
    return false;
}

void Manager::setSeed(int seed)
{
    int i = seeds.indexOf(seed);
    if(i == -1) // only add the seed if it's new
    {
        seeds.append(seed);
        curSeed++;
        emit action(QString("New seed: %1").arg(seeds[curSeed]));
        emit newSeed(seeds[curSeed]); 
    }
    else // otherwise switch to that seed
    {
        curSeed = i;
        emit newSeed(seeds[curSeed]);
    }
}

void Manager::prevMap()
{
    if(curSeed > 0)
        curSeed--;
    emit action(QString("New seed: %1").arg(seeds[curSeed]));
    emit newSeed(seeds[curSeed]);
    initialize();
}

void Manager::nextMap()
{
    if(curSeed < seeds.size() - 1)
        curSeed++;
    else
    {
        seeds.append((int)((double)qrand() / RAND_MAX * 1000)); // seeds are 0-999
        curSeed++;
    }
    emit action(QString("New seed: %1").arg(seeds[curSeed]));
    emit newSeed(seeds[curSeed]);
    initialize();
}

void Manager::go()
{
    if(!isSolutionComplete)
    {
        qsrand(seeds[curSeed]);
        // for some reason, several initial calls help obtain greater randomness
        for(int i = 0; i < 20; i++)
            qrand();

        emit action(QString("Go!"));

        void solution();
        solution();

        isSolutionComplete = true;

        emit solutionComplete();
    }
}
