#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logDialog(new LogDialog(this))
{
    ui->setupUi(this);

    connect(ui->logDialogButton, SIGNAL(clicked()),
            logDialog, SLOT(show()));
    connect(this, SIGNAL(newLogOutput(QString)),
            logDialog, SLOT(appendLogOutput(QString)));

    emit newLogOutput(QString("Line 1 of output"));
    emit newLogOutput(QString("Line 2 of output"));
    emit newLogOutput(QString("Line 3 of output"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
