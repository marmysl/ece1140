#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include "CTCDispatch.h"
#include "../../TrackModel/tracklayout.hpp"

int init_CTC(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    return 0;
}
