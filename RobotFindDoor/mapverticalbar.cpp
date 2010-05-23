#include "mapverticalbar.h"

#include <QGraphicsPixmapItem>

MapVerticalBar::MapVerticalBar(int seed) :
        Map(seed)
{ }

void MapVerticalBar::generate()
{
    newRobot("Jane");

    robot = new QGraphicsPixmapItem(QPixmap(":/images/robot"));
    robot->setPos(10, 10);
    addItem(robot);
}
