#include "solutionrunner.h"
#include <QMutex>
#include <QTimer>
#include <QTimeLine>
#include <QDebug>

SolutionRunner::SolutionRunner()
    : mutex(new QMutex(QMutex::Recursive)), running(false)
{
    connect(this, SIGNAL(firstAnimation()), this, SLOT(startAnimations()));
}

void SolutionRunner::run()
{
    exec();
}

void SolutionRunner::reset()
{
    mutex->lock();
    timelines.clear();
    running = false;
    mutex->unlock();
}

void SolutionRunner::addTimeLine(QTimeLine *t)
{
    mutex->lock();
    timelines.enqueue(t);
    if(!running)
        emit firstAnimation();
    mutex->unlock();
}

void SolutionRunner::startAnimations()
{
    mutex->lock();
    running = true;
    QTimeLine *t = timelines.dequeue();
    QTimer::singleShot(t->duration(), this, SLOT(nextAnimation()));
    t->start();
    mutex->unlock();
}

void SolutionRunner::nextAnimation()
{
    mutex->lock();
    if(timelines.empty())
    {
        running = false;
    }
    else
    {
        QTimeLine *t = timelines.dequeue();
        QTimer::singleShot(t->duration(), this, SLOT(nextAnimation()));
        t->start();
    }
    mutex->unlock();
}
