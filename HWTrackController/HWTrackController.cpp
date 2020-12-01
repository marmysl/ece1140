#include "HWTrackController.hpp"
#include "SerialPort.hpp"
#include "system_main.h"

#include <QThread>
#include <string>
#include <QTimer>

HWTrackController::HWTrackController()
{
    cout.flush();

    writeTimer = new QTimer(this);
    writeTimer->setInterval(ARDUINO_WAIT_TIME);

    // connect data receive method
    connect(&trackControllerPort, &SerialConn::dataReceived, this, &HWTrackController::recieveData);
    connect(writeTimer, &QTimer::timeout, this, &HWTrackController::writeData);

    // set up PLC timer
    plcTimer = new QTimer(this);
    plcTimer->setInterval(100);
    connect(plcTimer, &QTimer::timeout, &greenreg, &Region::runPLC);

    writeTimer->start();
    plcTimer->start();
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
         * Char 0 = Joystick left
         * Char 1 = Joystick right
         * Char 2 = Manually change Switch Position: 0 or 1
         * Char 3 = Manually activate railway crossing: 0 or 1
         * Char 4 = Update PLC Button: 0 or 1
         */

        if(data.length() == 5)
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
     * Char 18 = Failure Alert
     * Last character is a newline
     */

    string outgoing_s = "";

    // if (route = "Green Line") {
            int b = greenreg.getCurrentBlock();

            outgoing_s += to_string(greenreg.detectTrain(b, greenreg.getRoute()));

            outgoing_s += greenreg.getSection(b);

            if (b < 10) {
                outgoing_s += "0";
                outgoing_s += to_string(b);
            } else {
                 outgoing_s += b;
            }

            string suggestedSpeed(to_string(greenreg.getSuggestedSpeed(b)),0,4);
            outgoing_s += suggestedSpeed;

            string commandedSpeed(to_string(greenreg.getCommandedSpeed(b)),0,4);
            outgoing_s += commandedSpeed;

            string authority(to_string(greenreg.getAuthority(b)),0,4);
            outgoing_s += authority;

            string lights = "00"; // from the PLC
            outgoing_s += lights;

            outgoing_s += to_string(greenreg.detectFailure(b, greenreg.getRoute()));

            outgoing_s += "\n";
    //}

        /*
         if (route = "Red Line") {
            outgoing_s += to_string(redreg.detectTrain(redreg.getCurrentBlock(), redreg.getRoute()));

            outgoing_s += redreg.getSection(redreg.getCurrentBlock());

            if (redreg.getCurrentBlock() < 10) {
                outgoing_s += "0";
                outgoing_s += to_string(redreg.getCurrentBlock());
            } else {
                 outgoing_s += redreg.getCurrentBlock();
            }

            string suggestedSpeed(to_string(redreg.getSuggestedSpeed(redreg.getCurrentBlock())), 0, 4);
            outgoing_s += suggestedSpeed;

            string commandedSpeed(to_string(redreg.getCommandedSpeed(redreg.getCurrentBlock())), 0, 4);
            outgoing_s += commandedSpeed;

            string authority(to_string(redreg.getAuthority(redreg.getCurrentBlock())),0,4);
            outgoing_s += authority;

            string lights = "00";
            outgoing_s += lights;

            outgoing_s += "\n";
        } */

    // std::cout << "Outgoing Track Controller: " << outgoing_s << std::endl;
    cout.flush();

    strcpy(outgoingData, outgoing_s.c_str());
    trackControllerPort.writeString(outgoing_s);
}
