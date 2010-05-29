#include "robotimage.h"

QRectF RobotImage::boundingRect() const
{
    qreal penWidth = 3;
    return QRectF(-penWidth / 2 - ROBOT_SIZE/2, -penWidth / 2 - ROBOT_SIZE/2,
                  ROBOT_SIZE + penWidth, ROBOT_SIZE + penWidth);
}

void RobotImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{    
    painter->setPen(QPen(QBrush(QColor(201, 223, 242, 255)), 3));
    painter->setBrush(QColor(86, 90, 166, 255));

    painter->drawRoundedRect(-ROBOT_SIZE/2, -ROBOT_SIZE/2, ROBOT_SIZE, ROBOT_SIZE, 5, 5);

    painter->setPen(QPen(QBrush(QColor(201, 223, 242, 255)), 1));
    painter->drawEllipse(5*(ROBOT_SIZE/30) - ROBOT_SIZE/2, 5*(ROBOT_SIZE/30) - ROBOT_SIZE/2,
                         7*(ROBOT_SIZE/30), 7*(ROBOT_SIZE/30));
    painter->drawEllipse(18*(ROBOT_SIZE/30) - ROBOT_SIZE/2, 5*(ROBOT_SIZE/30) - ROBOT_SIZE/2,
                         7*(ROBOT_SIZE/30), 7*(ROBOT_SIZE/30));
}
