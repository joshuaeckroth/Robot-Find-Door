#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>

class QGraphicsPixmapItem;

class Viewport : public QGraphicsView
{
public:
    Viewport(QWidget *parent = 0);

private:
    QGraphicsScene *scene;
    QGraphicsPixmapItem *robot;
};

#endif // VIEWPORT_H
