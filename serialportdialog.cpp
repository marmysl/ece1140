#include "serialportdialog.h"
#include "ui_serialportdialog.h"
#include <QtSerialPort/QSerialPortInfo>

#include "SerialPort.hpp"

SerialPortDialog::SerialPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortDialog)
{
    ui->setupUi(this);

    on_refreshButton_clicked();
}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

void SerialPortDialog::on_buttonBox_accepted()
{
    // OK button clicked :D

    setTrackControllerPort(trackContPortInfo);
    setTrainControllerPort(trainContPortInfo);

    hide();
}

void SerialPortDialog::on_refreshButton_clicked()
{
    // Refresh button click'd

    portList = QSerialPortInfo::availablePorts();

    ui->trackPortCombo->clear();
    ui->trainPortCombo->clear();

    for( auto &port : portList )
    {
        QString pName = port.portName();
        ui->trackPortCombo->addItem(pName);
        ui->trainPortCombo->addItem(pName);
    }
}

void SerialPortDialog::on_trackPortCombo_currentIndexChanged(int index)
{
    trackContPortInfo = portList[index];
}

void SerialPortDialog::on_trainPortCombo_currentIndexChanged(int index)
{
    trainContPortInfo = portList[index];
}
