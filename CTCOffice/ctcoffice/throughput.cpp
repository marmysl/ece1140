#include "throughput.h"
#include "ui_throughput.h"
#include "mainwindow.h"

throughput::throughput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::throughput)
{
    ui->setupUi(this);

    line = "Green Line";

    TrackModel::Route *rte;
    rte = TrackModel::getRoute(line);

    for(TrackModel::Station *stat : rte->stations){
        passNum += TrackModel::getPassengersWaiting(line, stat->name);
    }
    ui->lblThroughput->setText(QString::number(passNum));

    timerID = startTimer(1000);
}

throughput::~throughput()
{
    delete ui;
    killTimer(timerID);
}

void throughput::timerEvent(QTimerEvent *event){
    passNum = 0;

    TrackModel::Route *rte;
    rte = TrackModel::getRoute(line);

    for(TrackModel::Station *stat : rte->stations){
        passNum += TrackModel::getPassengersWaiting(line, stat->name);
    }
    ui->lblThroughput->setText(QString::number(passNum));
}
