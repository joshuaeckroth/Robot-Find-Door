#ifndef DOOR_H
#define DOOR_H

#include <QString>

class Door
{
public:
    Door(QString _name, double _posX, double _posY);
    QString getName() const;
    double getPosX() const;
    double getPosY() const;

private:
    QString name;
    double posX;
    double posY;
};

#endif // DOOR_H
