#include "mapsimple.h"
#include "door.h"

#include <QGraphicsPixmapItem>

MapSimple::MapSimple(int seed) :
        Map(seed)
{ }

void MapSimple::generate()
{
    robot = new QGraphicsPixmapItem(QPixmap(":/images/robot"));
    robot->setPos(150, 150);
    addItem(robot);

    Door *door = new Door;
    doors.append(door);
}
