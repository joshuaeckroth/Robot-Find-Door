#ifndef ROBOTACTIONS_H
#define ROBOTACTIONS_H

#include <QString>

#include "robot.h"

Robot& getRobot(int index);
double robotForward(Robot &r, double dist);
void robotRotate(Robot &r, double angle);

#endif // ROBOTACTIONS_H
