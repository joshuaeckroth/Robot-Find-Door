#include <QtGui/QApplication>
#include "mainwindow.h"

//------------   Globals   ------------//
// Globals determining map dimensions  //
   qreal MAP_WIDTH  = 500.0;           //
   qreal MAP_HEIGHT = 500.0;           //
// Global determining robot dimension  //
   qreal ROBOT_SIZE = 30.0;            //
//-------------------------------------//

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
