#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QList>
#include <QString>
#include "robot.h"
#include "door.h"

// Import Defined Map Sizes from main.cpp
extern qreal MAP_WIDTH;
extern qreal MAP_HEIGHT;
// Import Defined Robot Size from main.cpp
extern qreal ROBOT_SIZE;

class Map : public QGraphicsScene
{
public:
    Map(int seed);
    ~Map();
    virtual void generate() = 0;
    QList<Door*> getDoors() const;

protected:
    Robot& newRobot(QString name);
    Door& newDoor(QString name);

    QList<Door*> doors;
    const double mapWidth, mapHeight;

private:
    int seed;
};

#endif // MAP_H
