#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "viewport.h"

Viewport::Viewport(QWidget *parent) :
        QGraphicsView(parent),
        scene(new QGraphicsScene())
{
    scene->setSceneRect(0, 0, 300, 300);
    scene->addText("Hello");
    scene->addLine(0, 0, 300, 300);

    robot = new QGraphicsPixmapItem(QPixmap(":/images/robot"));
    robot->setPos(150, 150);
    scene->addItem(robot);

    setScene(scene);
}
