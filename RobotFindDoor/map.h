#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QList>
#include <QString>


// Import Defined Map Sizes from main.cpp
extern qreal MAP_WIDTH;
extern qreal MAP_HEIGHT;
// Import Defined Robot Size from main.cpp
extern qreal ROBOT_SIZE;

class Robot;
class Door;
class Obstacle;
class QGraphicsItem;

class Map : public QGraphicsScene
{
public:
    Map(int seed);
    ~Map();
    virtual void generate() = 0;
    QList<Door*> getDoors() const;

protected:
    Robot *newRobot(QString name);
    Door *newDoor(QString name);
    void addObstacle(Obstacle *o);
    bool collidesWithAny(QGraphicsItem *item);

    QList<Door*> doors;
    QList<Robot*> robots;
    QList<Obstacle*> obstacles;
    const double mapWidth, mapHeight;

private:
    int seed;
};

#endif // MAP_H
