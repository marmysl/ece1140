#pragma once

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <iostream>

const int ARDUINO_WAIT_TIME = 2000;
const int ARDUINO_BUF_LENGTH = 255;

const qint32 baudRate = QSerialPort::Baud9600;
const QSerialPort::DataBits dataBits = QSerialPort::Data8;
const QSerialPort::StopBits stopBits = QSerialPort::OneStop;
const QSerialPort::Parity parity = QSerialPort::NoParity;
const QSerialPort::FlowControl flowControl = QSerialPort::HardwareControl;

extern QSerialPort trackControllerPort;
extern bool hwTrackControllerConnected;

extern QSerialPort trainControllerPort;
extern bool hwTrainControllerConnected;

void setTrackControllerPort( QSerialPortInfo &portInfo );
void setTrainControllerPort( QSerialPortInfo &portInfo );
