#ifndef HWTRACKCONTROLLER_H
#define HWTRACKCONTROLLER_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <QObject>

#include "hw_sw_interfaces.h"
#include "HWTrackController_main.h"
#include "SerialPort.hpp"
#include "hwplcui.h"

using namespace std;

class HWTrackController : public QObject, public ITrackController
{
    Q_OBJECT

    private:
        char incomingData[ARDUINO_BUF_LENGTH];
        char outgoingData[ARDUINO_BUF_LENGTH];
        QTimer *writeTimer;
        QTimer *plcTimer;

    public:
        HWTrackController();
        ~HWTrackController();

    public slots:
        void recieveData( char *buf, qint64 len );
        void writeData();
};

#endif
