#include "logdialog.h"
#include "ui_logdialog.h"

LogDialog::LogDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::LogDialog)
{
    ui->setupUi(this);
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::appendDebug(QString s)
{
    ui->logOutput->append(QString("<p><pre>%1</pre></p>").arg(s));
}

void LogDialog::appendAction(QString s)
{
    ui->logOutput->append(QString("<p><i>%1</i></p>").arg(s));
}


