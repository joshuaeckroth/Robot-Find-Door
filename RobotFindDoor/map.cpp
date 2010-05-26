#include "map.h"
#include "door.h"
#include "robot.h"
#include "manager.h"
#include <QString>
#include <cmath>

Map::Map(int _seed) :
        QGraphicsScene(), mapWidth(500.0), mapHeight(500.0), seed(_seed)
{
    setBackgroundBrush(Qt::gray);
    // Add outside barrier.
    addRect(0.0, 0.0, mapWidth, mapHeight,           
            QPen(QBrush(QColor(88, 41, 217, 75)), 3),
            QBrush(QColor(88, 41, 217, 75)));


    // Add inside barrier:
    // Determine the Robot's Longest Radius:
    qreal buffer_width  = sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));
    addRect(0.0+buffer_width/2, 0.0+buffer_width/2, mapWidth-buffer_width, mapHeight-buffer_width,
            QPen(QBrush(QColor(88, 41, 217, 75)), 3),
            QBrush(Qt::white));
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

    double posX, posY;

    do
    {
        posX = mapWidth * (double)qrand() / RAND_MAX;
        posY = mapHeight * (double)qrand() / RAND_MAX;
    }
    while(m->spaceOccupied(posX, posY));

    double angle = 2.0 * 3.141592653589 * (double)qrand() / RAND_MAX;

    Robot *r = new Robot(name, angle, posX, posY);
    addItem((QGraphicsItem*)r->getImage());
    m->addRobot(r);
    return *r;
}

Door& Map::newDoor(QString name)
{
    Manager *m = Manager::instance();

    int side = (qrand() % 4);
    double pos = (double)qrand() / RAND_MAX;

    Door *d;
    switch(side)
    {
    case 0: // left
        d = new Door(name, 0.0, pos);
        break;
    case 1: // right
        d = new Door(name, mapWidth, pos);
        break;
    case 2: // top
        d = new Door(name, pos, 0.0);
        break;
    case 3: // bottom
        d = new Door(name, pos, mapHeight);
        break;
    default: ;
    }

    m->addDoor(d);
    return *d;
}
