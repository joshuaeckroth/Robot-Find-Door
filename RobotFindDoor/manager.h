#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QList>

class Robot;
class Door;
class Map;
class Viewport;
class SolutionRunner;

class Manager : public QObject
{
    Q_OBJECT
public:
    static Manager* instance();
    int getSeed() const;
    bool hasPrevSeed() const;
    void setSeed(int seed);
    int getCurSeed() const;
    int getNumSeeds() const;
    void setViewport(Viewport *v);
    void initialize();
    void addRobot(Robot *r);
    Robot* getRobot(int index);
    void addDoor(Door *d);
    Door* getDoor(int index);

    bool spaceOccupied(double posX, double posY);

signals:
    void action(QString);
    void newSeed(int);
    void solutionComplete();

public slots:
    void prevMap();
    void nextMap();
    void go();

private slots:
    void solutionCompleted();

private:
    Manager();
    ~Manager() {};
    Manager(Manager const&);
    Manager& operator=(Manager const&);
    static Manager* pInstance;
    void deleteAllDoors();
    void deleteAllRobots();

    QList<int> seeds;
    int curSeed;
    QList<Robot*> robots;
    QList<Door*> doors;

    Map *map;
    Viewport *viewport;
    SolutionRunner *solutionRunner;
    bool isSolutionComplete;
};

#endif // MANAGER_H
