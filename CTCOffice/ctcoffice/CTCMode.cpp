#include "CTCMode.h"
#include <QDebug>
#include <string>
#include <sstream>
#include <QTextStream>
#include <QApplication>
#include "system_main.h"
#include "ctc_main.h"
#include "schedule.h"

// mode = 0 = Automatic
// mode = 1 = Manual
CTCMode::CTCMode()
{
    mode = 1;
}

void CTCMode::setMode(bool m){

    if(m == 0){
        automaticDispatch();
        qDebug() << "Set Dispatch Mode to Automatic";
    }
    else if(m == 1){
        manualDispatch();
        qDebug() << "Set Dispatch Mode to Manual";
    }
    else{
        //throw error
    }
}

bool CTCMode::getMode(){
    return mode;
}

void CTCMode::sm(bool m){
    mode = m;
}

CTCDispatch train1;
CTCDispatch train2;
CTCDispatch train3;
CTCDispatch train4;
CTCDispatch train5;
CTCDispatch train6;
CTCDispatch train7;
CTCDispatch train8;
CTCDispatch train9;
CTCDispatch train10;

void CTCMode::automaticDispatch()
{
    mode = 0;

    m = &ctcMainWindow->m;
    schedule *s = ctcMainWindow->autoSchedule;

    if(!s){
        // prompt for schedule if not already initialized
        ctcMainWindow->autoSchedule = new schedule();
        s = ctcMainWindow->autoSchedule;
    }

    // one more chance to load schedule
    if(!s->loadComplete) {
        // modal dialog, must have schedule before continuing
        s->exec();
    }

    if(!s->loadComplete) {
        // really? no schedule? go fix it and come back later
        qDebug() << "No schedule loaded, no trains will be dispatched in Automatic Mode";
        return;
    }

    if(!m){
        qDebug() << "Problem with setting mode and sending to SW Train Controller";
        return;
    }

    if(s->stat.front() == "Pioneer"){
        line = "Green Line";
    }
    else if(s->stat.front() == "Shadyside"){
        line = "Red Line";
    }

    train1.setCTCMode(m);
    train1.setLine(line);
    train1.setTimeStart(s->t1.front());
    train1.setTimeArrival(s->t1.back());
    train1.setBlock(s->blocks.back());
    time = train1.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train1); });

    train2.setCTCMode(m);
    train2.setLine(line);
    train2.setTimeStart(s->t2.front());
    train2.setTimeArrival(s->t2.back());
    train2.setBlock(s->blocks.back());
    time = train2.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train2); });

    train3.setCTCMode(m);
    train3.setLine(line);
    train3.setTimeStart(s->t3.front());
    train3.setTimeArrival(s->t3.back());
    train3.setBlock(s->blocks.back());
    time = train3.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train3); });

    train4.setCTCMode(m);
    train4.setLine(line);
    train4.setTimeStart(s->t4.front());
    train4.setTimeArrival(s->t4.back());
    train4.setBlock(s->blocks.back());
    time = train4.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train4); });

    train5.setCTCMode(m);
    train5.setLine(line);
    train5.setTimeStart(s->t5.front());
    train5.setTimeArrival(s->t5.back());
    train5.setBlock(s->blocks.back());
    time = train5.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train5); });

    train6.setCTCMode(m);
    train6.setLine(line);
    train6.setTimeStart(s->t6.front());
    train6.setTimeArrival(s->t6.back());
    train6.setBlock(s->blocks.back());
    time = train6.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train6); });

    train7.setCTCMode(m);
    train7.setLine(line);
    train7.setTimeStart(s->t7.front());
    train7.setTimeArrival(s->t7.back());
    train7.setBlock(s->blocks.back());
    time = train7.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train7); });

    train8.setCTCMode(m);
    train8.setLine(line);
    train8.setTimeStart(s->t8.front());
    train8.setTimeArrival(s->t8.back());
    train8.setBlock(s->blocks.back());
    time = train8.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train8); });

    train9.setCTCMode(m);
    train9.setLine(line);
    train9.setTimeStart(s->t9.front());
    train9.setTimeArrival(s->t9.back());
    train9.setBlock(s->blocks.back());
    time = train9.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train9); });

    train10.setCTCMode(m);
    train10.setLine(line);
    train10.setTimeStart(s->t10.front());
    train10.setTimeArrival(s->t10.back());
    train10.setBlock(s->blocks.back());
    time = train10.setTimeDelay();
    QTimer::singleShot(time/(systemClock->timeScale), [=]() { test(train10); });

}

void CTCMode::manualDispatch()
{
    mode = 1;
}

void CTCMode::test(CTCDispatch train){
    CTCSignals c1;
    train.dispatch(c1);
}
