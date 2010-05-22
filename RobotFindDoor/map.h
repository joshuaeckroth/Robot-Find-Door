#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QList>

class Door;

class Map : public QGraphicsScene
{
public:
    Map(int seed);
    ~Map();
    virtual void generate() = 0;
    QList<Door*> getDoors() const;

protected:
    QList<Door*> doors;

private:
    int seed;
};

#endif // MAP_H
