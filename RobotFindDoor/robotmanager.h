#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <QList>

class Robot;

class RobotManager
{
public:
    static RobotManager* instance();
    void addRobot(Robot *r);
    void deleteAllRobots();

private:
    RobotManager() {};
    ~RobotManager() {};
    RobotManager(RobotManager const&);
    RobotManager& operator=(RobotManager const&);
    static RobotManager* pInstance;

    QList<Robot*> robots;
};

#endif // ROBOTMANAGER_H
