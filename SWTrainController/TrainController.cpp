#include <iostream>
#include <iomanip>

#include "TrainController.h"
#include "TrainCGUI.h"
#include  "../TrainModel/Train.h"

#include <QApplication>

using namespace std;

TrainController :: TrainController(int argc, char *argv[]) //Constructor: creates train controller object and executes GUI
{
    QApplication a(argc, argv);
    MainWindow w;
    //Train* train = new Train(3, argc, argv); // create train object each time a TC is initialized
    Train train(3, argc, argv); // create train object each time a TC is initialized
    w.show();
    a.exec();

}


void TrainController :: calculatePower()
{
    // calculate power here
    power = 2; //arbitrary value for iteration #2
}


void TrainController :: decode(unsigned signal)  // decodes track circuit into speed & auth //switch to void?
{
    // add stuff here

    //temporary - debugging
    authority = 10.5;
    suggestedSpeed = signal;

}
