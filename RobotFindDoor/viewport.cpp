#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "viewport.h"
#include "mapsimple.h"

Viewport::Viewport(QWidget *parent) :
        QGraphicsView(parent)
{
    map = (Map*)(new MapSimple(0));
    map->generate();

    setScene(map);
}
