#include <iostream>
#include <iomanip>

#include "TrainController.h"
#include "TrainCGUI.h"

#include <QApplication>

using namespace std;

TrainController :: TrainController(int argc, char *argv[]) //Constructor: creates train controller object and executes GUI
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

}


void TrainController :: calculatePower()
{
    // calculate power here
    power = 2; //arbitrary value for iteration #2
}


double TrainController :: decode(unsigned)  // decodes track circuit into speed & auth
{
    // add stuff here
    return 0;
}
