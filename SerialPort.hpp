/*
* Author: Manash Kumar Mandal
* Modified Library introduced in Arduino Playground which does not work
* This works perfectly
* LICENSE: MIT
*/

#pragma once

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <iostream>

const qint32 baudRate = QSerialPort::Baud9600;
const QSerialPort::DataBits dataBits = QSerialPort::Data8;
const QSerialPort::StopBits stopBits = QSerialPort::OneStop;
const QSerialPort::Parity parity = QSerialPort::NoParity;
const QSerialPort::FlowControl flowControl = QSerialPort::HardwareControl;

QSerialPort trackControllerPort;
extern bool trackControlConnected;

QSerialPort trainControllerPort;
extern bool trainControlConnected;

void setTrackControllerPort( QSerialPortInfo &portInfo );
void setTrainControllerPort( QSerialPortInfo &portInfo );
