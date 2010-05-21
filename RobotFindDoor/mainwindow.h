#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LogDialog;
class Manager;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    LogDialog *logDialog;
    Manager *m;
};

#endif // MAINWINDOW_H
