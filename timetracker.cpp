#include "timetracker.h"
#include <cmath>

TimeTracker *systemClock;

TimeTracker::TimeTracker( QDateTime startTime, int resolution, float scale, QObject *parent) :
    QObject(parent), timeScale(scale), resolution(resolution), lastUpdate(startTime)
{
    updateTimer.setParent(this);
    updateTimer.setInterval(resolution);
    connect(&updateTimer, &QTimer::timeout, this, &TimeTracker::doTimeUpdate);
}

void TimeTracker::play()
{
    updateTimer.start();
}

void TimeTracker::pause()
{
    updateTimer.stop();
}

void TimeTracker::changeTime( const QDateTime &newTime )
{
    bool running = updateTimer.isActive();
    pause();

    lastUpdate = newTime;

    if( running ) play();
}

void TimeTracker::doTimeUpdate()
{
    qint64 delta = roundf(resolution * timeScale);
    QDateTime newTime = lastUpdate.addMSecs(delta);

    timeAdvanced(newTime, delta);

    lastUpdate = newTime;
}
