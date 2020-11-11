#include <iostream>
#include <iomanip>

#include "TrainCGUI.h"
#include "SWTrainController_main.h"

#include <QApplication>

using namespace std;

SWTrainController :: SWTrainController(int numCars, std::string lineType) //Constructor: creates train and executes GUI
{
    cout << "Train Controller created" << endl;
    cout.flush();

    TrainControlWindow *w = new TrainControlWindow();
    train = new Train(numCars, lineType); // create train object each time a TC is initialized
    w->train = train;

    w->show();

}

