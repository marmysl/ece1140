#ifndef TRAINCONTROLLER_H
#define TRAINCONTROLLER_H

#include "hw_sw_interfaces.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <QObject>
#include "SpeedRegulator.h"
#include "TrainModel/Train.h"
#include "SerialPort.hpp"
#include "BeaconDecoder.h"
#include "../CTCOffice/ctcoffice/CTCMode.h"


using namespace std;

class TrainController : public QObject, public ITrainController
{
    Q_OBJECT

    private:
        char incomingData[ARDUINO_BUF_LENGTH];
        char outgoingData[ARDUINO_BUF_LENGTH];
        Train *trainModel;
        SpeedRegulator *speedRegulator;
        BeaconDecoder *beacon;
        CTCMode *mode;

        QTimer *writeTimer;

	public:

        //Constructor and Destructor
        TrainController(CTCMode *m, int numCars, std::string lineType);
        ~TrainController();

        //Method that writes data to the Serial Port
        void writeData();

    public slots:

        //Method that receives data from the Serial Port
        void recieveData( char *buf, qint64 len );
};

#endif
