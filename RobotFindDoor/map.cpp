#include "map.h"
#include "door.h"
#include "robot.h"
#include "manager.h"
#include <QString>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <cmath>

Map::Map(int _seed) :
        QGraphicsScene(), mapWidth(MAP_WIDTH), mapHeight(MAP_HEIGHT), seed(_seed)
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
