#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>

class Map;

class Viewport : public QGraphicsView
{
public:
    Viewport(QWidget *parent = 0);
    void setMap(Map *_map);
    void zoom();

private:
    void mousePressEvent(QMouseEvent *e);

    Map *map;
};

#endif // VIEWPORT_H
