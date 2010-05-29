#include "map.h"
#include "door.h"
#include "robot.h"
#include "obstacle.h"
#include "manager.h"
#include "robotimage.h"
#include <QString>
#include <QGraphicsItemAnimation>
#include <QGraphicsItem>
#include <QTimeLine>
#include <QList>
#include <cmath>

Map::Map(int _seed) :
        QGraphicsScene(), mapWidth(MAP_WIDTH), mapHeight(MAP_HEIGHT), seed(_seed)
{
    setBackgroundBrush(Qt::gray);
    qreal buffer_width  = sqrt(2*(ROBOT_SIZE*ROBOT_SIZE));

    QGraphicsRectItem border(0.0, 0.0, mapWidth, mapHeight);
    QGraphicsRectItem inside(0.0+buffer_width/2, 0.0+buffer_width/2, mapWidth-buffer_width, mapHeight-buffer_width);
    QPainterPath shape = border.shape();
    shape = shape.subtracted(inside.shape());
    addPath(shape, QPen(QColor(88, 41, 217, 75)), QBrush(QColor(88, 41, 217, 75)));
}

Map::~Map()
{
    while(!doors.isEmpty())
        delete doors.takeFirst();
    while(!robots.isEmpty())
        delete robots.takeFirst();
    while(!obstacles.isEmpty())
        delete obstacles.takeFirst();
}

QList<Door*> Map::getDoors() const
{
    return doors;
}

Robot *Map::newRobot(QString name)
{
    Manager *m = Manager::instance();

    double posX, posY;

    Robot *r = NULL;
    double angle = 360.0 * (double)qrand() / RAND_MAX;
    do
    {
        if(r) { delete r; r = NULL; }

        posX = mapWidth * (double)qrand() / RAND_MAX;
        posY = mapHeight * (double)qrand() / RAND_MAX;
        r = new Robot(name, angle, posX, posY);
    }
    while(collidesWithAny((QGraphicsItem*)r->getImage()));

    addItem((QGraphicsItem*)r->getImage());

    m->addRobot(r);
    robots.append(r);
    return r;
}

Door *Map::newDoor(QString name)
{
    Manager *m = Manager::instance();

    Door *d = NULL;
    do
    {
        if(d) { delete d; d = NULL; }

        int side = (qrand() % 4);
        double posX = mapWidth * (double)qrand() / RAND_MAX;
        double posY = mapHeight * (double)qrand() / RAND_MAX;

        switch(side)
        {
        case 0: // left
            d = new Door(name, 0.0, posY);
            break;
        case 1: // right
            d = new Door(name, mapWidth, posY);
            break;
        case 2: // top
            d = new Door(name, posX, 0.0);
            break;
        case 3: // bottom
            d = new Door(name, posX, mapHeight);
            break;
        default: ;
        }
    }
    while(collidesWithAny(d));

    addItem((QGraphicsItem*)d);

    m->addDoor(d);
    doors.append(d);
    return d;
}

void Map::addObstacle(Obstacle *o)
{
    addItem((QGraphicsItem*)o);

    obstacles.append(o);
}

bool Map::collidesWithAny(QGraphicsItem *item)
{
    //QList<QGraphicsItem*> collisions = collidingItems(item);

    //return !collisions.empty();
    return false;
}
