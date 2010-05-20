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

void LogDialog::appendLogOutput(QString s)
{
    ui->logOutput->append(QString("<i>%1</i>\n").arg(s));
}

