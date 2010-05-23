#include "map.h"
#include "door.h"
#include "robot.h"
#include "manager.h"
#include <QString>

Map::Map(int _seed) :
        QGraphicsScene(), seed(_seed)
{
    setSceneRect(0, 100, 0, 100);
}

Map::~Map()
{
    while(!doors.isEmpty())
        delete doors.takeFirst();
}

QList<Door*> Map::getDoors() const
{
    return doors;
}

Robot& Map::newRobot(QString name)
{
    Manager *m = Manager::instance();

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
