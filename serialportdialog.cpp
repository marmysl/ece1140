#include "serialportdialog.h"
#include "ui_serialportdialog.h"
#include <QSerialPortInfo>

#include "SerialPort.hpp"

SerialPortDialog::SerialPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortDialog)
{
    ui->setupUi(this);

    on_refreshButton_clicked();

    on_trackPortCombo_currentIndexChanged(0);
    on_trainPortCombo_currentIndexChanged(0);
}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

void SerialPortDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    // Apply button clicked

    if( ui->trackEnabled->isChecked() && (trackContPortInfo != NULL) )
    {
        trackControllerPort.connectPort(*trackContPortInfo);
    }
    else
    {
        trackControllerPort.disconnect();
    }

    if( ui->trainEnabled->isChecked() && (trainContPortInfo != NULL) )
    {
        trainControllerPort.connectPort(*trainContPortInfo);
    }
    else
    {
        trainControllerPort.disconnect();
    }

    setResult(Accepted);

    hide();
}

static bool refreshInProgress = false;

void SerialPortDialog::on_refreshButton_clicked()
{
    // Refresh button click'd

    portList = QSerialPortInfo::availablePorts();

    refreshInProgress = true;

    ui->trackPortCombo->clear();
    ui->trainPortCombo->clear();

    for( auto &port : portList )
    {
        QString pName = port.portName();
        ui->trackPortCombo->addItem(pName);
        ui->trainPortCombo->addItem(pName);
    }

    refreshInProgress = false;
}

void SerialPortDialog::on_trackPortCombo_currentIndexChanged(int index)
{
    if( refreshInProgress ) return;
    if( index >= 0 && index < portList.length() )
    {
        trackContPortInfo = &(portList[index]);
    }
    else
    {
        trackContPortInfo = NULL;
    }
}

void SerialPortDialog::on_trainPortCombo_currentIndexChanged(int index)
{
    if( refreshInProgress ) return;
    if( index >= 0 && index < portList.length() )
    {
        trainContPortInfo = &(portList[index]);
    }
    else
    {
        trackContPortInfo = NULL;
    }
}
