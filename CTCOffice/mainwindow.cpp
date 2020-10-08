#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <CTCDispatch.h>
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

    ui->comboDestination->addItem("Station B");
    ui->comboDestination->addItem("Station C");
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

    CTCDispatch ctc;
    ctc.setLine(line);

    qDebug() << QString::fromStdString(line);
}

void MainWindow::on_timeStart_userTimeChanged(const QTime &time)
{
    QString qs;
    qs = time.toString("hh:mm");

    std::string startTime;
    startTime = qs.toStdString();

    CTCDispatch ctc;
    ctc.setTimeStart(startTime);

    qDebug() << QString::fromStdString(startTime);
}

void MainWindow::on_timeArrival_userTimeChanged(const QTime &time)
{
    QString qs;
    qs = time.toString("hh:mm");

    std::string arrivalTime;
    arrivalTime = qs.toStdString();

    CTCDispatch ctc;
    ctc.setTimeStart(arrivalTime);

    qDebug() << QString::fromStdString(arrivalTime);
}

void MainWindow::on_btnDispatch_clicked()
{
    CTCDispatch ctc;

    ctc.dispatch();
}

void MainWindow::on_comboDestination_currentIndexChanged(const QString &arg1)
{
    std::string station;
    QString qs = arg1;

    station = qs.toStdString();

    CTCDispatch ctc;
    ctc.setStation(station);

    qDebug() << QString::fromStdString(station);
}

void MainWindow::on_btnCancel_clicked()
{

}
