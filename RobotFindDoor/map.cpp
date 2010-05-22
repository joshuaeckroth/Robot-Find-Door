#include "map.h"
#include "door.h"

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
