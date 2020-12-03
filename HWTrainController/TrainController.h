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
        bool stopTimerStarted;
        bool stopAlreadyOccurred;
        QDateTime start;
        QDateTime now;

        QTimer *writeTimer;

	public:

        /*!
            Constructor that initializes a TrainController object with a CTCMode object, the
            number of cars the train it controls will have, and the line that the train is on
            @pre: a TrainController object does not exist
            @post: a TrainController object exists with initialized member variables
            @param: none
            @throw: none
            @return: none
        */
        TrainController(CTCMode *m, int numCars, std::string lineType);

        /*!
            Destructor that ensures each pointer is deleted without any memory leaks
            @pre: a TrainController object exists
            @post: a TrainController object no longer exists and all dynamically allocated memory
                   has been eliminated
            @param: none
            @throw: none
            @return: none
        */
        ~TrainController();

        /*!
            Function that creates a string and sends it to the Arduino via Serial Port
            @pre: none
            @post: data is written to the Serial Port for the Arduino to receive
            @param: none
            @throw: none
            @return: none
        */
        void writeData();

        /*!
            Function that continuously reads for Beacons and stops the train when a beacon
            indicates that it should do so
            @pre: none
            @post: the train reacts to different flags decoded from the beacon
            @param: none
            @throw: none
            @return: none
        */
        void updateBeaconData(std::string headlights);

    public slots:

        /*!
            Function that reads in a string from the Arduino via Serial Port
            @pre: none
            @post: data is recieved from Serial Port via the Serial Port and methods are called
                   according to each character
            @param: char buf : contains the data from the Arduino read in from the Serial Port
            @param: qint64 len : contains the length of the buffer from the Arduino
            @throw: none
            @return: none
        */
        void recieveData( char *buf, qint64 len );
};

#endif
