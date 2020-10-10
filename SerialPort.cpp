#include "SerialPort.hpp"

bool trackControlConnected = false;
bool trainControlConnected = false;

void setTrackControllerPort( QSerialPortInfo &portInfo )
{
    trackControllerPort.setPort(portInfo);
    trackControllerPort.setBaudRate(baudRate);
    trackControllerPort.setDataBits(dataBits);
    trackControllerPort.setStopBits(stopBits);
    trackControllerPort.setParity(parity);
    trackControllerPort.setFlowControl(flowControl);

    trackControlConnected = trackControllerPort.open(QIODevice::ReadWrite);
}

void setTrainControllerPort( QSerialPortInfo &portInfo )
{
    trainControllerPort.setPort(portInfo);
    trainControllerPort.setBaudRate(baudRate);
    trainControllerPort.setDataBits(dataBits);
    trainControllerPort.setStopBits(stopBits);
    trainControllerPort.setParity(parity);
    trainControllerPort.setFlowControl(flowControl);

    trainControlConnected = trainControllerPort.open(QIODevice::ReadWrite);
}


