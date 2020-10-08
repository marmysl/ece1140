#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include "CTCDispatch.h"
#include <QTime>
#include <QString>
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboLine->addItem("Blue Line");

    ui->comboDestinationType->addItem("Station");
    ui->comboDestinationType->addItem("Block");

    QFont font = ui->btnDispatch->font();
    font.setPointSize(60);
    ui->btnDispatch->setFont(font);

    QFont font1 = ui->btnCancel->font();
    font1.setPointSize(60);
    ui->btnCancel->setFont(font1);

    QFont font2 = ui->comboLine->font();
    font2.setPointSize(60);
    ui->btnCancel->setFont(font2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboLine_currentIndexChanged(const QString &arg1)
{
    std::string line;
    QString qs = arg1;

    line = qs.toStdString();

    ctc.setLine(line);
}

void MainWindow::on_timeStart_userTimeChanged(const QTime &time)
{
    QString qs;
    qs = time.toString("hh:mm");

    std::string startTime;
    startTime = qs.toStdString();

    ctc.setTimeStart(startTime);
}

void MainWindow::on_timeArrival_userTimeChanged(const QTime &time)
{
    QString qs;
    qs = time.toString("hh:mm");

    std::string arrivalTime;
    arrivalTime = qs.toStdString();

    ctc.setTimeArrival(arrivalTime);
}

void MainWindow::on_btnDispatch_clicked()
{
    ctc.dispatch();
}

void MainWindow::on_comboDestination_currentIndexChanged(const QString &arg1)
{
    std::string choice;
    QString qs = arg1;

    choice = qs.toStdString();

    ctc.setDestinationType(choice);
}

void MainWindow::on_comboDestinationType_currentIndexChanged(const QString &arg1)
{
    std::string destinationType;
    QString qs = arg1;

    destinationType = qs.toStdString();

    ui->comboDestination->clear();
    if(destinationType == "Station"){
        ui->comboDestination->addItem("Station B");
        ui->comboDestination->addItem("Station C");
    }
    else if(destinationType == "Block"){
        ui->comboDestination->addItem("Block 1");
        ui->comboDestination->addItem("Block 2");
        ui->comboDestination->addItem("Block 3");
        ui->comboDestination->addItem("Block 4");
        ui->comboDestination->addItem("Block 5");
        ui->comboDestination->addItem("Block 6");
        ui->comboDestination->addItem("Block 7");
        ui->comboDestination->addItem("Block 8");
        ui->comboDestination->addItem("Block 9");
        ui->comboDestination->addItem("Block 10");
        ui->comboDestination->addItem("Block 11");
        ui->comboDestination->addItem("Block 12");
        ui->comboDestination->addItem("Block 13");
        ui->comboDestination->addItem("Block 14");
        ui->comboDestination->addItem("Block 15");
    }

    ctc.setDestinationType(destinationType);
}
