#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logdialog.h"
#include "manager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logDialog(new LogDialog(this))
{
    ui->setupUi(this);

    connect(ui->logDialogButton, SIGNAL(clicked()), logDialog, SLOT(show()));

    m = Manager::instance();
    connect(m, SIGNAL(action(QString)), logDialog, SLOT(appendAction(QString)));

    void solution();
    solution();
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
