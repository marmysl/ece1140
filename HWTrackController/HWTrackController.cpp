#include "HWTrackController.hpp"
#include "SerialPort.hpp"
#include "system_main.h"

#include <QThread>
#include <string>
#include <QTimer>

HWTrackController::HWTrackController()
{
    std::cout << "here" << std::endl;
    cout.flush();

    writeTimer = new QTimer(this);
    writeTimer->setInterval(ARDUINO_WAIT_TIME);

    // connect data receive method
    connect(&trackControllerPort, &SerialConn::dataReceived, this, &HWTrackController::recieveData);
    connect(writeTimer, &QTimer::timeout, this, &HWTrackController::writeData);

    writeTimer->start();
}

HWTrackController::~HWTrackController()
{
    delete writeTimer;
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

    outgoing_s += to_string(greenreg.detectTrain(greenreg.getCurrentBlock(), greenreg.getRoute()));

    outgoing_s += greenreg.getSection(greenreg.getCurrentBlock());

    if (greenreg.getCurrentBlock() < 10) {
        outgoing_s += "0";
        outgoing_s += to_string(greenreg.getCurrentBlock());
    } else {
         outgoing_s += greenreg.getCurrentBlock();
    }

    string suggestedSpeed(to_string(greenreg.getSuggestedSpeed(greenreg.getCurrentBlock())), 0, 4);
    outgoing_s += suggestedSpeed;

    string commandedSpeed(to_string(greenreg.getCommandedSpeed(greenreg.getCurrentBlock())), 0, 4);
    outgoing_s += commandedSpeed;

    string authority(to_string(greenreg.getAuthority(greenreg.getCurrentBlock())),0,4);
    outgoing_s += authority;

    string lights = "00";
    outgoing_s += lights;

    outgoing_s += "\n";

    //std::cout << "Outgoing Track Controller: " << outgoing_s << std::endl;
    //cout.flush();

    strcpy(outgoingData, outgoing_s.c_str());

    trackControllerPort.writeString(outgoing_s);
}
