#include "robotimage.h"
#include <QTransform>
#include <QPainterPath>
#include <QDebug>

RobotImage::RobotImage()
{ }

RobotImage::RobotImage(const RobotImage &r)
{
    setPos(r.pos());
    setTransform(r.transform());
}

QRectF RobotImage::boundingRect() const
{
    QPainterPath p;
    p.addRoundedRect(-ROBOT_SIZE/2, -ROBOT_SIZE/2, ROBOT_SIZE, ROBOT_SIZE, 5, 5);
    QTransform t = transform();
    QPainterPath p_trans = t.map(p);
    QRectF bound_trans = p_trans.boundingRect();
    return bound_trans;
}

void RobotImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{    
    painter->setPen(QPen(QBrush(QColor(201, 223, 242, 255)), 3));
    painter->setBrush(QColor(86, 90, 166, 255));

    painter->drawRoundedRect(-ROBOT_SIZE/2, -ROBOT_SIZE/2, ROBOT_SIZE, ROBOT_SIZE, 5, 5);

    painter->setPen(QPen(QBrush(QColor(201, 223, 242, 255)), 1));
    painter->drawEllipse(18*(ROBOT_SIZE/30) - ROBOT_SIZE/2, 5*(ROBOT_SIZE/30) - ROBOT_SIZE/2,
                         7*(ROBOT_SIZE/30), 7*(ROBOT_SIZE/30));
    painter->drawEllipse(18*(ROBOT_SIZE/30) - ROBOT_SIZE/2, 3*(ROBOT_SIZE/30),
                         7*(ROBOT_SIZE/30), 7*(ROBOT_SIZE/30));
}
