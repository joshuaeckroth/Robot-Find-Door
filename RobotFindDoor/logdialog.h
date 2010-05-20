#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>

namespace Ui {
    class LogDialog;
}

class LogDialog : public QDialog
{
    Q_OBJECT
public:
    LogDialog(QWidget *parent = 0);
    ~LogDialog();

public slots:
    void appendLogOutput(QString s);

private:
    Ui::LogDialog *ui;

};

#endif // LOGDIALOG_H
