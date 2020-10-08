#include <iostream>
#include "SerialPort.hpp"
#include <stdio.h>
#include <string>
#include "CabinControls.h"
#include "SpeedRegulator.h"
#include "../TrainModel/Train.h"
#include "../TrainModel/Train.cpp"
#include "TrainController.h"
#include "TrainController.cpp"

using namespace std;

int main()
{
	TrainController tc;
	tc.dispatch();
}