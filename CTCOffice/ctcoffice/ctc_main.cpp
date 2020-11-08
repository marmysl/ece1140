#include "mainwindow.h"
#include "Files.h"

#include <QApplication>

#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include "CTCDispatch.h"
#include "../../TrackModel/tracklayout.hpp"

MainWindow *ctcMainWindow;

int init_CTC(int argc, char *argv[])
{
    ctcMainWindow = new MainWindow();
    ctcMainWindow->show();

    return 0;
}
