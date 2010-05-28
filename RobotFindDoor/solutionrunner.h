#ifndef SOLUTIONRUNNER_H
#define SOLUTIONRUNNER_H

#include <QThread>
#include <QQueue>

class QTimeLine;
class QMutex;

class SolutionRunner : public QThread
{
    Q_OBJECT
public:
    SolutionRunner();
    void run();
    void reset();

signals:
    void solutionComplete();
    void animationComplete();
    void firstAnimation();

public slots:
    void addTimeLine(QTimeLine *t);

private slots:
    void startAnimations();
    void nextAnimation();

private:
    QQueue<QTimeLine*> timelines;
    QMutex *mutex;
    bool running;
    QTimeLine *currentTimeLine;
};

#endif // SOLUTIONRUNNER_H
