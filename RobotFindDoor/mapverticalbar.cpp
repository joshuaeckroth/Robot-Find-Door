#include "mapverticalbar.h"
#include "obstacle.h"
#include <QGraphicsPixmapItem>

MapVerticalBar::MapVerticalBar(int seed) :
        Map(seed)
{ }

void MapVerticalBar::generate()
{
    newRobot("Jane");
    newDoor("Door 1");

    bool top = (qrand() % 2 == 0);
    Obstacle *o = NULL;
    double posX, posY;
    do
    {
        if(o) { delete o; o = NULL; }

        posX = mapWidth * (double)qrand() / RAND_MAX;
        posY = mapHeight * (double)qrand() / RAND_MAX;

        if(posY < 100.0) continue;
        if(posY > mapHeight - 100.0) continue;

        if(top)
            o = new Obstacle(QRectF(posX, 0.0, 5.0, posY - 50.0)); // save space for robot
        else
            o = new Obstacle(QRectF(posX, posY + 50.0, 5.0, mapHeight - posY - 50.0));
    }
    while(o == NULL || collidesWithAny(o));
    addObstacle(o);
}
