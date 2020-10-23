#ifndef TRAINCONTROLLER_H
#define TRAINCONTROLLER_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <QObject>
#include "CabinControls.h"
#include "SpeedRegulator.h"
#include "TrainModel/Train.h"
#include "SerialPort.hpp"

using namespace std;

class TrainController : public QObject
{
    Q_OBJECT

    private:
        char incomingData[ARDUINO_BUF_LENGTH];
        char outgoingData[ARDUINO_BUF_LENGTH];
		Train *train_model;
		CabinControls *cabin_controller;
		SpeedRegulator *speed_regulator;

	public:
		TrainController();
        ~TrainController();
		void writeData(int delayTime);
		string getInput();
		string getOutput();
		void dispatch();

    public slots:
        void recieveData( char *buf, qint64 len );
};

#endif
