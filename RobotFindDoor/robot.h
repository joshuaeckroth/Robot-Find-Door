#ifndef ROBOT_H
#define ROBOT_H

#include <QString>

class Robot
{
public:
    Robot(QString _name, double _angle, double _posX, double _posY);

private:
    QString name;
    double angle;
    double posX;
    double posY;
};

#endif // ROBOT_H
