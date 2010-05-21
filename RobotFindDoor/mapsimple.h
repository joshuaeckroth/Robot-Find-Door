#ifndef MAPSIMPLE_H
#define MAPSIMPLE_H

#include "map.h"

class QGraphicsPixmapItem;

class MapSimple : public Map
{
public:
    MapSimple(int seed);
    void generate();

private:
    QGraphicsPixmapItem *robot;
};

#endif // MAPSIMPLE_H
