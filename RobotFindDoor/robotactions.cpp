
#include "robot.h"
#include "manager.h"

Robot *getRobot(int index)
{
    return Manager::instance()->getRobot(index);
}


