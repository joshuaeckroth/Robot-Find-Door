#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QList>

class Robot;

class Manager : public QObject
{
    Q_OBJECT
public:
    static Manager* instance();
    int getNextSeed();
    void addRobot(Robot *r);
    void deleteAllRobots();
    bool spaceOccupied(double posX, double posY);

signals:
    void action(QString);

private:
    Manager();
    ~Manager() {};
    Manager(Manager const&);
    Manager& operator=(Manager const&);
    static Manager* pInstance;

    QList<int> seeds;
    QList<Robot*> robots;
};

#endif // MANAGER_H
