#pragma once

#include <QSerialPort>
#include <QObject>
#include <QTimer>
#include <iostream>

const int ARDUINO_WAIT_TIME = 500;
const int ARDUINO_BUF_LENGTH = 255;

class SerialConn : public QObject
{
    Q_OBJECT

private:
    QSerialPort port;
    QTimer *recvTimer;
    char buffer[ARDUINO_BUF_LENGTH + 1];

public:
    explicit SerialConn(QObject *parent = nullptr);
    ~SerialConn();

    bool connectPort( QSerialPortInfo& portInfo );
    void disconnect();
    bool isConnected();

    void write( const char *data, qint64 length );
    void writeLine( const char *data, qint64 length );

    void writeString( const std::string &data );
    void writeStringLine( const std::string& data );

public slots:
    void checkIncoming();

signals:
    void dataReceived( char *buf, qint64 length );
};


extern SerialConn trackControllerPort;
extern SerialConn trainControllerPort;
