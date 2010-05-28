#ifndef MAPVERTICALBAR_H
#define MAPVERTICALBAR_H

#include "map.h"

class QGraphicsPixmapItem;

class MapVerticalBar : public Map
{
public:
    MapVerticalBar(int seed);
    void generate();
};

#endif // MAPVERTICALBAR_H
