#ifndef TRAINCONTROLLER_H
#define TRAINCONTROLLER_H

#include <iostream>
#include <stdio.h>
#include <string>
#include "CabinControls.h"
#include "SpeedRegulator.h"
#include "TrainModel/Train.h"
#include <QtSerialPort/QSerialPort>

using namespace std;

class TrainController
{
	private:
		char portName[9] = "\\\\.\\COM4";
		char incomingData[255];
		char outgoingData[255];
        QSerialPort *arduino;
		Train *train_model;
		CabinControls *cabin_controller;
		SpeedRegulator *speed_regulator;
	public:
		TrainController();
		~TrainController();
		void recieveData();
		void writeData(int delayTime);
		string getInput();
		string getOutput();
		void dispatch();

};

#endif
