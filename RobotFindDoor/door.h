#ifndef DOOR_H
#define DOOR_H

#include <QString>
#include <QGraphicsItem>

class Door : public QGraphicsItem
{
public:
    Door(QString _name, double _posX, double _posY);
    QString getName() const;
    double getPosX() const;
    double getPosY() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString name;
    double posX;
    double posY;
    QRectF rect;
};

#endif // DOOR_H
