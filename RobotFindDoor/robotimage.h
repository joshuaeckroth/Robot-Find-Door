#ifndef ROBOTIMAGE_H
#define ROBOTIMAGE_H

#include <QGraphicsItem>
#include <QPainter>

// Import Defined Robot Size from main.cpp
extern qreal ROBOT_SIZE;

class RobotImage : public QGraphicsItem
{
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
};

#endif // ROBOTIMAGE_H
