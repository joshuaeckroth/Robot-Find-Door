#ifndef ROBOTACTIONS_H
#define ROBOTACTIONS_H

#include <QString>

#include "robot.h"

Robot& newRobot(QString name);
double robotForward(Robot &r, double dist);
void robotRotate(Robot &r, double angle);

#endif // ROBOTACTIONS_H
