#include "door.h"
#include <QPainter>
#include <QString>

extern double ROBOT_SIZE;

Door::Door(QString _name, double _posX, double _posY, QString _side) :
        QGraphicsItem(0), name(_name), posX(_posX), posY(_posY),
        rect(QRectF(posX - ROBOT_SIZE/2.0, posY - ROBOT_SIZE/2.0, ROBOT_SIZE, ROBOT_SIZE)),
        side(_side)
{ }

QString Door::getName() const
{
    return name;
}

double Door::getPosX() const
{
    if (side == "LEFT") return posX+ROBOT_SIZE;
    else if (side == "RIGHT") return posX-ROBOT_SIZE;
    else return posX;
}

double Door::getPosY() const
{
    if (side == "TOP") return posY+ROBOT_SIZE;
    else if (side == "BOTTOM") return posY-ROBOT_SIZE;
    else return posY;
}

QString Door::getSide() const
{
    return side;
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

