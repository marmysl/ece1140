#include "CTCMode.h"
#include <QDebug>
#include <string>
#include <sstream>
#include <QTextStream>
#include <QApplication>

#include "system_main.h"
#include "schedule.h"
#include "ctc_main.h"

// mode = 0 = Automatic
// mode = 1 = Manual
CTCMode::CTCMode()
{
    mode = 0;
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

void CTCMode::automaticDispatch()
{
    mode = 0;
    m->mode = 0;

    schedule *s = ctcMainWindow->s;
    //s.on_loadSchedule_clicked();

    if(!s){
        qDebug() << "No schedule loaded, no trains will be dispatched in Automatic Mode";
        return;
    }

    CTCDispatch train1;

    //Fix these hard coded once the blue line issue is fixed
    train1.setCTCMode(m);
    train1.setLine("Green Line");
    train1.setTimeStart(s->t1.front());
    train1.setTimeArrival(s->t1.back());
    train1.setBlock(s->blocks.back());
    CTCSignals c1;
    train1.dispatch(c1);

    CTCDispatch train2;

    train2.setCTCMode(m);
    train2.setLine("Green Line");
    train2.setTimeStart(s->t2.front());
    train2.setTimeArrival(s->t2.back());
    train2.setBlock(s->blocks.back());
    CTCSignals c2;
    train2.dispatch(c2);

    CTCDispatch train3;

    train3.setCTCMode(m);
    train3.setLine("Green Line");
    train3.setTimeStart(s->t3.front());
    train3.setTimeArrival(s->t3.back());
    train3.setBlock(s->blocks.back());
    CTCSignals c3;
    train3.dispatch(c3);

    CTCDispatch train4;

    train4.setCTCMode(m);
    train4.setLine("Green Line");
    train4.setTimeStart(s->t4.front());
    train4.setTimeArrival(s->t4.back());
    train4.setBlock(s->blocks.back());
    CTCSignals c4;
    train4.dispatch(c4);

    CTCDispatch train5;

    train5.setCTCMode(m);
    train5.setLine("Green Line");
    train5.setTimeStart(s->t5.front());
    train5.setTimeArrival(s->t5.back());
    train5.setBlock(s->blocks.back());
    CTCSignals c5;
    train5.dispatch(c5);

    CTCDispatch train6;

    train6.setCTCMode(m);
    train6.setLine("Green Line");
    train6.setTimeStart(s->t6.front());
    train6.setTimeArrival(s->t6.back());
    train6.setBlock(s->blocks.back());
    CTCSignals c6;
    train6.dispatch(c6);

    CTCDispatch train7;

    train7.setCTCMode(m);
    train7.setLine("Green Line");
    train7.setTimeStart(s->t7.front());
    train7.setTimeArrival(s->t7.back());
    train7.setBlock(s->blocks.back());
    CTCSignals c7;
    train7.dispatch(c7);

    CTCDispatch train8;

    train8.setCTCMode(m);
    train8.setLine("Green Line");
    train8.setTimeStart(s->t8.front());
    train8.setTimeArrival(s->t8.back());
    train8.setBlock(s->blocks.back());
    CTCSignals c8;
    train8.dispatch(c8);

    CTCDispatch train9;

    train9.setCTCMode(m);
    train9.setLine("Green Line");
    train9.setTimeStart(s->t9.front());
    train9.setTimeArrival(s->t9.back());
    train9.setBlock(s->blocks.back());
    CTCSignals c9;
    train9.dispatch(c9);

    CTCDispatch train10;

    train10.setCTCMode(m);
    train10.setLine("Green Line");
    train10.setTimeStart(s->t10.front());
    train10.setTimeArrival(s->t10.back());
    train10.setBlock(s->blocks.back());
    CTCSignals c10;
    train10.dispatch(c10);

}

void CTCMode::manualDispatch()
{
    mode = 1;
}

