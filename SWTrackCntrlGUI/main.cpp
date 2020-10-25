#include "SWTrackCntrlGUI.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SWTrackCntrlGUI w;
    w.show();
    return a.exec();
}
