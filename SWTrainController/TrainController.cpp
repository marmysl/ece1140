#include <iostream>
#include <iomanip>
#include "TrainController.h"
using namespace std;

TrainController :: TrainController() //Constructor
{


}

double TrainController :: getPower() //accessor for power in kW
{
    return power;
}


void TrainController :: calculatePower()
{
    // calculate power here

}


double TrainController :: decode(unsigned)  // decodes track circuit into speed & auth
{
    // add stuff here
    return 0;
}
