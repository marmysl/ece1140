#ifndef HWTRACKCONTROLLER_H
#define HWTRACKCONTROLLER_H

#include "hw_sw_interfaces.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <QObject>
#include "Region.hpp"
#include "SerialPort.hpp"

using namespace std;

class HWTrackController : public QObject, public ITrackController
{
    Q_OBJECT

    private:
        char incomingData[ARDUINO_BUF_LENGTH];
        char outgoingData[ARDUINO_BUF_LENGTH];
        Region *reg;

        QTimer *writeTimer;

    public:
        HWTrackController();
        ~HWTrackController();
        void writeData();

    public slots:
        void recieveData( char *buf, qint64 len );
};

#endif
