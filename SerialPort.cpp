#include "SerialPort.hpp"

QSerialPort trackControllerPort;
bool hwTrackControllerConnected = false;

QSerialPort trainControllerPort;
bool hwTrainControllerConnected = false;

void setTrackControllerPort( QSerialPortInfo *portInfo )
{
    trackControllerPort.setPort(*portInfo);
    trackControllerPort.setBaudRate(baudRate);
    trackControllerPort.setDataBits(dataBits);
    trackControllerPort.setStopBits(stopBits);
    trackControllerPort.setParity(parity);
    trackControllerPort.setFlowControl(flowControl);

    hwTrackControllerConnected = trackControllerPort.open(QIODevice::ReadWrite);
}

void setTrainControllerPort( QSerialPortInfo *portInfo )
{
    trainControllerPort.setPort(*portInfo);
    trainControllerPort.setBaudRate(baudRate);
    trainControllerPort.setDataBits(dataBits);
    trainControllerPort.setStopBits(stopBits);
    trainControllerPort.setParity(parity);
    trainControllerPort.setFlowControl(flowControl);

    hwTrainControllerConnected = trainControllerPort.open(QIODevice::ReadWrite);
}


