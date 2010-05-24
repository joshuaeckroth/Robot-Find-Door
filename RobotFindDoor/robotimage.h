#ifndef ROBOTIMAGE_H
#define ROBOTIMAGE_H

#include <QGraphicsItem>
#include <QPainter>

class RobotImage : public QGraphicsItem
{
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif // ROBOTIMAGE_H
