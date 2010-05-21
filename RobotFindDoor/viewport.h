#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>

class Map;

class Viewport : public QGraphicsView
{
public:
    Viewport(QWidget *parent = 0);

private:
    Map *map;
};

#endif // VIEWPORT_H
