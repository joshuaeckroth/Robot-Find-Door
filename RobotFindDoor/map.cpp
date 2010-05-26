#include "map.h"
#include "door.h"
#include "robot.h"
#include "manager.h"
#include <QString>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

Map::Map(int _seed) :
        QGraphicsScene(), mapWidth(500.0), mapHeight(500.0), seed(_seed)
{
    setBackgroundBrush(Qt::gray);
    addRect(0.0, 0.0, mapWidth, mapHeight,
            QPen(QBrush(QColor(217, 88, 41, 255)), 3),
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

    double angle = 360.0 * (double)qrand() / RAND_MAX;

    Robot *r = new Robot(name, angle, posX, posY);
    addItem((QGraphicsItem*)r->getImage());

    QTimeLine *timer = new QTimeLine(5000);
    timer->setFrameRange(0, 100);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem((QGraphicsItem*)r->getImage());
    animation->setTimeLine(timer);
    for(int i = 0; i < 200; i++)
    {
        animation->setRotationAt(i/200.0, 360.0 * i / 200.0);
    }
    timer->start();

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
