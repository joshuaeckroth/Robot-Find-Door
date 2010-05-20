#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LogDialog;

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

signals:
    void newLogOutput(QString);

private:
    Ui::MainWindow *ui;
    LogDialog *logDialog;
};

#endif // MAINWINDOW_H
