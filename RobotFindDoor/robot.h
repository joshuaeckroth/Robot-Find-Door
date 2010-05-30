#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QString>
#include <QQueue>
#include <QVector>

#include "map.h"
// Import Defined Robot Size from main.cpp
extern qreal ROBOT_SIZE;

class RobotImage;
class SolutionRunner;
class QTimeLine;
class QGraphicsItemAnimation;

class Robot : public QObject
{
    Q_OBJECT
public:
    Robot(QString _name, double _angle, double _posX, double _posY);
    ~Robot();
    QString getName() const;
    double getAngle() const;
    double getPosX() const;
    double getPosY() const;    
    RobotImage *getImage();   
    double moveForward(double dist);
    void rotate(double angle);
    void setSolutionRunner(SolutionRunner *s);
    void setMap(Map *m);
    bool collides();

signals:
    void addTimeLine(QTimeLine*);

private slots:
    void animationComplete();

private:
    struct properties
    {
        double angle;
        double posX;
        double posY;
    };
    Map *myMap;
    QQueue<struct Robot::properties> propsQueue;

    QVector<QTimeLine*> timelines;
    QVector<QGraphicsItemAnimation*> animations;

    QString name;
    RobotImage *robotImage;
    SolutionRunner *solutionRunner;

    // checkBounds():
    //    Modifies posX, posY to ensure robot is within the bounds regardless of rotated angle.
    //    returns true if no adjustments were required.
    bool checkBounds();
};

#endif // ROBOT_H
