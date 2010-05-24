#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTransform>
#include <QMouseEvent>
#include <QDebug>

#include "viewport.h"
#include "mapsimple.h"

Viewport::Viewport(QWidget *parent) :
        QGraphicsView(parent), map(NULL)
{
    setRenderHint(QPainter::Antialiasing);
}

void Viewport::setMap(Map *_map)
{
    map = _map;
    setScene(map);
}

void Viewport::zoom()
{
    QTransform transform;
    transform.scale(0.9 * width()/map->width(), 0.9 * height()/map->height());
    setTransform(transform);
}

void Viewport::mousePressEvent(QMouseEvent *e)
{

}
