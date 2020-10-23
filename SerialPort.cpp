#include "SerialPort.hpp"

// SerialConn Definitions
//------------------------------------------------------------------------------------

SerialConn::SerialConn(QObject *parent) : QObject(parent)
{
    buffer[ARDUINO_BUF_LENGTH] = '\0';
    recvTimer = new QTimer(this);
    connect(recvTimer, &QTimer::timeout, this, &SerialConn::checkIncoming);
    recvTimer->setInterval(ARDUINO_WAIT_TIME);
}

SerialConn::~SerialConn()
{
    delete recvTimer;
}

bool SerialConn::connectPort(QSerialPortInfo &portInfo)
{
    if( port.isOpen() ) port.close();

    port.setPort(portInfo);
    port.setBaudRate(QSerialPort::Baud9600);
    port.setDataBits(QSerialPort::Data8);
    port.setStopBits(QSerialPort::OneStop);
    port.setParity(QSerialPort::NoParity);

    bool isOpen = port.open(QIODevice::ReadWrite);
    if( isOpen ) recvTimer->start();
    else recvTimer->stop();

    return isOpen;
}

void SerialConn::disconnect()
{
    if( port.isOpen() ) port.close();
}

bool SerialConn::isConnected()
{
    return port.isOpen();
}

const char newline = '\n';

void SerialConn::write( const char *data, qint64 length )
{
    if( !port.isOpen() ) return;
    port.write(data, length);
}

void SerialConn::writeLine( const char *data, qint64 length )
{
    if( !port.isOpen() ) return;
    port.write(data, length);
    port.write(&newline, 1);
}

void SerialConn::writeString( const std::string &data )
{
    write(data.c_str(), data.length());
}

void SerialConn::writeStringLine( const std::string& data )
{
    writeLine(data.c_str(), data.length());
}

void SerialConn::checkIncoming()
{
    if( port.canReadLine() )
    {
        qint64 nRead = port.readLine(buffer, ARDUINO_BUF_LENGTH);
        if( nRead > 0 ) dataReceived(buffer, nRead);
    }
}

//------------------------------------------------------------------------------------
// End SerialConn

SerialConn trackControllerPort;
SerialConn trainControllerPort;

