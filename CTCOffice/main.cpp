#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <vector>
#include <time.h>
#include <CTCSignals.h>
#include <CTCDispatch.h>
#include <cstdlib>

int main(int argc, char *argv[])
{
    //CTCDispatch ctc;
    //ctc.setTimeStart("15:45");
    //ctc.setTimeArrival("18:30");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    //ctc.dispatch();
    //ctc.setAuthority("Station B");
    //ctc.setSpeed("Station C", 8, 10);

    return 0;
}
