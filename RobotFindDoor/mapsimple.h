#ifndef MAPSIMPLE_H
#define MAPSIMPLE_H

#include "map.h"

class QGraphicsPixmapItem;

class MapSimple : public Map
{
public:
    MapSimple(int seed);
    void generate();
};

#endif // MAPSIMPLE_H
