#include "door.h"
#include <QPainter>
#include <QString>

extern double ROBOT_SIZE;

Door::Door(QString _name, double _posX, double _posY) :
        QGraphicsItem(0), name(_name), posX(_posX), posY(_posY),
        rect(QRectF(posX - ROBOT_SIZE/2.0, posY - ROBOT_SIZE/2.0, ROBOT_SIZE, ROBOT_SIZE))
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

