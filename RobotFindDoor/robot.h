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
    Robot(QString _name, double _angle, double _posX, double _posY, Map *_map);
    ~Robot();
    QString getName() const;
    double getAngle() const;
    double getPosX() const;
    double getPosY() const;    
    RobotImage *getImage();   
    double moveForward(double dist);
    void rotate(double angle);
    void setSolutionRunner(SolutionRunner *s);

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
    QQueue<struct Robot::properties> propsQueue;

    QVector<QTimeLine*> timelines;
    QVector<QGraphicsItemAnimation*> animations;

    QString name;
    RobotImage *robotImage;
    SolutionRunner *solutionRunner;
    Map *map;
};

#endif // ROBOT_H
