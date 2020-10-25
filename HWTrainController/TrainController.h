#ifndef TRAINCONTROLLER_H
#define TRAINCONTROLLER_H

#include "hw_sw_interfaces.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <QObject>
#include "CabinControls.h"
#include "SpeedRegulator.h"
#include "TrainModel/Train.h"
#include "SerialPort.hpp"

using namespace std;

class TrainController : public QObject, public ITrainController
{
    Q_OBJECT

    private:
        char incomingData[ARDUINO_BUF_LENGTH];
        char outgoingData[ARDUINO_BUF_LENGTH];
		CabinControls *cabin_controller;
		SpeedRegulator *speed_regulator;

        QTimer *writeTimer;

	public:
		TrainController();
        ~TrainController();
        void writeData();
		string getInput();
		string getOutput();
        void dispatch();

    public slots:
        void recieveData( char *buf, qint64 len );
};

#endif
