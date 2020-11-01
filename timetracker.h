#pragma once

#include <QObject>
#include <QTimer>
#include <QDateTime>

class TimeTracker : public QObject
{
    Q_OBJECT

public:
    float timeScale;

    explicit TimeTracker( QDateTime startTime, int resolution, float scale, QObject *parent = nullptr);

    void play();
    void pause();

    /*! Move the mk1 system time to the given value (does not trigger timeAdvanced) */
    void changeTime( const QDateTime &newTime );
    QDateTime currentTime();

    int getResolution();
    void setResolution( int res );

private:
    int resolution;

    QTimer updateTimer;
    QDateTime lastUpdate;

private slots:
    void doTimeUpdate();

signals:
    /*! Emitted when the system time is advanced */
    void timeAdvanced( const QDateTime &newTime, qint64 deltaMs );
};

extern TimeTracker *systemClock;
