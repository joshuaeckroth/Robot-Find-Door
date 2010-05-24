#ifndef ROBOT_H
#define ROBOT_H

#include <QString>

class RobotImage;

class Robot
{
public:
    Robot(QString _name, double _angle, double _posX, double _posY);
    ~Robot();
    QString getName() const;
    double getAngle() const;
    double getPosX() const;
    double getPosY() const;
    RobotImage *getImage() const;

private:
    QString name;
    double angle;
    double posX;
    double posY;
    RobotImage *robotImage;
};

#endif // ROBOT_H
