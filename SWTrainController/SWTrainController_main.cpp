#include <iostream>
#include <iomanip>

#include "SWTrainController_main.h"

#include <QApplication>

using namespace std;

SWTrainController :: SWTrainController(int argc, char *argv[]) //Constructor: creates train controller object and executes GUI
{
    cout << "Train Controller created" << endl;
    cout.flush();

    TrainControlWindow *w = new TrainControlWindow();
    train = new Train(3); // create train object each time a TC is initialized
    w->train = train;

    w->show();

}

/* ------------------------------------------ UNUSED ------------------------------------------------
void SWTrainController :: calculatePower()
{
    // calculate power here
    power = 2; //arbitrary value for iteration #2
}


void SWTrainController :: decode(unsigned signal)  // decodes track circuit into speed & auth //switch to void?
{
    // add stuff here

    //temporary - debugging
    authority = 10.5;
    suggestedSpeed = signal;

}
*/