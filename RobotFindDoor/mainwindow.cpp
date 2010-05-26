#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logdialog.h"
#include "manager.h"

#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logDialog(new LogDialog(this))
{
    ui->setupUi(this);

    connect(ui->logDialogButton, SIGNAL(clicked()), logDialog, SLOT(show()));

    m = Manager::instance();
    connect(m, SIGNAL(action(QString)), logDialog, SLOT(appendAction(QString)));
    connect(m, SIGNAL(newSeed(int)), this, SLOT(newSeed(int)));
    connect(m, SIGNAL(solutionComplete()), this, SLOT(solutionComplete()));
    connect(ui->setSeedButton, SIGNAL(clicked()), this, SLOT(setSeed()));
    connect(ui->prevMapButton, SIGNAL(clicked()), m, SLOT(prevMap()));
    connect(ui->nextMapButton, SIGNAL(clicked()), m, SLOT(nextMap()));
    connect(ui->goButton, SIGNAL(clicked()), m, SLOT(go()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(reset()));

    int seed = std::time(NULL) % 1000;
    qsrand(seed);
    m->setViewport(ui->viewport);
    m->setSeed(seed);
    m->initialize();

    ui->resetButton->setDisabled(true);
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

void MainWindow::setSeed()
{
    m->setSeed(ui->seedInput->text().toInt());
    m->initialize();
}

void MainWindow::newSeed(int seed)
{
    ui->seedInput->setText(QString("%1").arg(seed));
    if(m->hasPrevSeed())
        ui->prevMapButton->setDisabled(false);
    else
        ui->prevMapButton->setDisabled(true);
    ui->mapLabel->setText(QString("Map %1/%2+")
                          .arg(m->getCurSeed()+1)
                          .arg(m->getNumSeeds()));
}

void MainWindow::reset()
{
    m->initialize();
    ui->resetButton->setDisabled(true);
    ui->goButton->setDisabled(false);
}

void MainWindow::solutionComplete()
{
    ui->resetButton->setDisabled(false);
    ui->goButton->setDisabled(true);
}
