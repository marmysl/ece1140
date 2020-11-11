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

        //Arrays for serial port communication
        char incomingData[ARDUINO_BUF_LENGTH];
        char outgoingData[ARDUINO_BUF_LENGTH];

        //Pointers to classes to distribute arduino data
        Train *trainModel;
        SpeedRegulator *speedRegulator;
        BeaconDecoder *beacon;
        CTCMode *mode;

        //Timer to write/read data
        QTimer *writeTimer;

	public:

        //Constructor and Destructor
        TrainController(CTCMode *m);
        ~TrainController();

        //Method that writes data to the Serial Port
        void writeData();

        //Methods used for testing:


    public slots:

        //Method that receives data from the Serial Port
        void recieveData( char *buf, qint64 len );
};

#endif
