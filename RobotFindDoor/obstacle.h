#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsItem>

class Obstacle : public QGraphicsItem
{
public:
    Obstacle(QRectF _rect);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    const QRectF rect;
};

#endif // OBSTACLE_H
