#include "obstacle.h"
#include <QPainter>

Obstacle::Obstacle(QRectF _rect)
    : QGraphicsItem(0), rect(_rect)
{ }

QRectF Obstacle::boundingRect() const
{
    return rect;
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(242, 149, 68));
    painter->drawRect(rect);
}
