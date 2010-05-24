#include "mapsimple.h"

#include <QGraphicsPixmapItem>

MapSimple::MapSimple(int seed) :
        Map(seed)
{ }

void MapSimple::generate()
{
    newRobot("Bob");
    newDoor("Main Door");
}
