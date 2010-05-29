#include "door.h"
#include <QPainter>
#include <QString>

Door::Door(QString _name, double _posX, double _posY) :
        QGraphicsItem(0), name(_name), posX(_posX), posY(_posY),
        rect(QRectF(posX - 10, posY - 10, 20, 20))
{ }

QString Door::getName() const
{
    return name;
}

double Door::getPosX() const
{
    return posX;
}

double Door::getPosY() const
{
    return posY;
}

QRectF Door::boundingRect() const
{
    return rect;
}

void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor(217, 88, 41));
    painter->drawRect(rect);
}

