#include "solutionrunner.h"
#include <QMutex>
#include <QTimer>
#include <QTimeLine>
#include <QDebug>

SolutionRunner::SolutionRunner()
    : mutex(new QMutex(QMutex::Recursive)), running(false), currentTimeLine(NULL)
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
    if(currentTimeLine)
        currentTimeLine->stop();
    currentTimeLine = NULL;
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
    currentTimeLine = timelines.dequeue();
    QTimer::singleShot(currentTimeLine->duration(), this, SLOT(nextAnimation()));
    currentTimeLine->start();
    mutex->unlock();
}

void SolutionRunner::nextAnimation()
{
    mutex->lock();
    if(running)
    {
        emit animationComplete();
        if(timelines.empty())
        {
            running = false;
            currentTimeLine = NULL;
            emit solutionComplete();
        }
        else
        {
            currentTimeLine = timelines.dequeue();
            QTimer::singleShot(currentTimeLine->duration(), this, SLOT(nextAnimation()));
            currentTimeLine->start();
        }
    }
    mutex->unlock();
}
