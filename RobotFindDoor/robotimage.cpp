#include "robotimage.h"

QRectF RobotImage::boundingRect() const
{
    qreal penWidth = 3;
    return QRectF(-penWidth / 2, -penWidth / 2,
                  30 + penWidth, 30 + penWidth);
}

void RobotImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    painter->setPen(QPen(QBrush(QColor(201, 223, 242, 255)), 3));
    painter->setBrush(QColor(86, 90, 166, 255));

    painter->drawRoundedRect(0, 0, 30, 30, 5, 5);

    painter->setPen(QPen(QBrush(QColor(201, 223, 242, 255)), 1));
    painter->drawEllipse(5, 8, 7, 7);
    painter->drawEllipse(18, 8, 7, 7);
}
