#include "map.h"

Map::Map(int _seed) :
        QGraphicsScene(), seed(_seed)
{
    setSceneRect(0, 100, 0, 100);
}
