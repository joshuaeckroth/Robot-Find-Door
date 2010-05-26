#include <QtGui/QApplication>
#include "mainwindow.h"

//------------   Globals   ------------//
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
