#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>

class Map : public QGraphicsScene
{
public:
    Map(int seed);
    virtual void generate() = 0;

private:
    int seed;
};

#endif // MAP_H
