#include "HWTrackController.hpp"
#include "SerialPort.hpp"
#include "system_main.h"

#include <QThread>
#include <string>
#include <QTimer>

//Region reg;

HWTrackController::HWTrackController()
{
    //regptr = &reg;



    writeTimer = new QTimer();
    writeTimer->setInterval(ARDUINO_WAIT_TIME);

    // connect data receive method
    connect(&trackControllerPort, &SerialConn::dataReceived, this, &HWTrackController::recieveData);
    connect(writeTimer, &QTimer::timeout, this, &HWTrackController::writeData);

    writeTimer->start();
}

HWTrackController::~HWTrackController()
{
    delete writeTimer;
   // delete regptr;
}

void HWTrackController::recieveData( char *buf, qint64 len )
{
    memcpy(incomingData, buf, len);
    incomingData[len] = '\0';

    if( len >= 0 )
    {
        string data(incomingData);
        cout << "Incoming Length: " << data.length() << endl;
        std::cout << "Incoming Track Controller: " << data << std::endl;

        /*
         * Char 0-1 = Block Number (int)
         * Char 2 = Manual Switch : 0 or 1
         * Char 3 = Railway Switches Switch : 0 or 1
         * Char 4 = Railway Crossing Switch : 0 or 1
         * Char 5-6 = Color of the Lights : 00, 01, 10 (green, yellow, red)
         * Char 7 = State of the PLC Button: 0 or 1
         * Char 8 = State of the View Track Button: 0 or 1
         * Char 9-10 = Joystick: 00 (left), 01 (right), 10 (up), 11 (down)
         * Char 11 = newline char
         */

        if(data.length() == 12)
        {
            std::cout << "Incoming Track Controller: " << data << std::endl;
        }
    }
}

void HWTrackController::writeData()
{
    /*
     * Char 0 = Block Occupancy
     * Char 1 = Current Section
     * Char 2-3 = Current Block
     * Char 4-7 = Suggested Speed
     * Char 8-11 = Commanded Speed
     * Char 12-15 = Authority
     * Char 16-17 = Lights
     * Last character is a newline
     */

    string outgoing_s = "";

    // test string
    //outgoing_s += "1A0412.011.030.001";
    //outgoing_s += "\n";

    //outgoing_s += to_string(regptr->detectTrain(regptr->getCurrentBlock()));

    //std::cout << "Outgoing Track Controller: " << outgoing_s << std::endl;

    strcpy(outgoingData, outgoing_s.c_str());

    trackControllerPort.writeString(outgoing_s);
}
