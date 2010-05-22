#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QList>

class Robot;
class Map;
class Viewport;

class Manager : public QObject
{
    Q_OBJECT
public:
    static Manager* instance();
    int getSeed() const;
    bool hasPrevSeed() const;
    void setSeed(int seed);
    void setViewport(Viewport *v);
    void initialize();
    void addRobot(Robot *r);
    void deleteAllRobots();
    bool spaceOccupied(double posX, double posY);

signals:
    void action(QString);
    void newSeed(int);

public slots:
    void prevMap();
    void nextMap();
    void go();

private:
    Manager();
    ~Manager() {};
    Manager(Manager const&);
    Manager& operator=(Manager const&);
    static Manager* pInstance;

    QList<int> seeds;
    int curSeed;
    QList<Robot*> robots;

    Map *map;
    Viewport *viewport;
};

#endif // MANAGER_H
