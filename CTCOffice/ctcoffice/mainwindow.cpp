#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include "CTCDispatch.h"
#include <QTime>
#include <QString>
#include <iostream>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "CTCHashmap.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , autoSchedule(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboDestinationType->addItem("Station");
    ui->comboDestinationType->addItem("Block");

    updateRoute();

    ctc.setCTCMode(&m);

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

    if(line.empty()){
        return;
    }
    TrackModel::Route *rte;
    rte = TrackModel::getRoute(line);

    std::string destinationType = ui->comboDestinationType->currentText().toStdString();

    if(destinationType == "Station"){
        for(TrackModel::Station *stat : rte->stations){
            for(TrackModel::Block *blk : stat->attachedBlocks){
                QString sName = QString("%0 (%1)").arg(QString::fromStdString(stat->name)).arg(blk->id);
                ui->comboDestination->addItem(sName);
            }
        }
    }
    else if(destinationType == "Block"){
        for(auto &blk : rte->blocks){
            if(blk.second->id != 0){
                 ui->comboDestination->addItem(QString::number(blk.second->id));
            }
        }
    }
}

void MainWindow::on_timeStart_userTimeChanged(const QTime &time)
{
    ctc.setTimeStart(time);
}

void MainWindow::on_timeArrival_userTimeChanged(const QTime &time)
{
    ctc.setTimeArrival(time);
}

void MainWindow::on_btnDispatch_clicked()
{
    int time;
    time  = ctc.setTimeDelay();

    timerID = startTimer(time);
}

void MainWindow::on_comboDestination_currentIndexChanged(const QString &arg1)
{
    ctc.setDestination(arg1, ui->comboDestinationType->currentText());
}

void MainWindow::on_comboDestinationType_currentIndexChanged(const QString &arg1)
{
    std::string destinationType;
    QString qs = arg1;

    destinationType = qs.toStdString();

    ui->comboDestination->clear();

    std::string l = ctc.getline();
    if(l.empty()){
        return;
    }
    TrackModel::Route *rte;
    rte = TrackModel::getRoute(l);

    if(destinationType == "Station"){
        for(TrackModel::Station *stat : rte->stations){
            for(TrackModel::Block *blk : stat->attachedBlocks){
                QString sName = QString("%0 (%1)").arg(QString::fromStdString(stat->name)).arg(blk->id);
                ui->comboDestination->addItem(sName);
            }
        }
    }
    else if(destinationType == "Block"){
        for(auto &blk : rte->blocks){
            if(blk.second->id != 0){
                 ui->comboDestination->addItem(QString::number(blk.second->id));
            }
        }
    }
}

void MainWindow::on_AutomaticButton_clicked()
{
    ui->AutomaticButton->setEnabled(false);
    ui->ManualButton->setEnabled(true);

    ui->comboLine->setEnabled(false);
    ui->comboDestination->setEnabled(false);
    ui->comboDestinationType->setEnabled(false);
    ui->timeStart->setEnabled(false);
    ui->timeArrival->setEnabled(false);
    ui->btnDispatch->setEnabled(false);
    ui->btnCancel->setEnabled(false);

    ui->AutomaticButton->repaint();

    m.setMode(0);
}

void MainWindow::on_ManualButton_clicked()
{
    ui->ManualButton->setEnabled(false);
    ui->AutomaticButton->setEnabled(true);

    ui->comboLine->setEnabled(true);
    ui->comboDestination->setEnabled(true);
    ui->comboDestinationType->setEnabled(true);
    ui->timeStart->setEnabled(true);
    ui->timeArrival->setEnabled(true);
    ui->btnDispatch->setEnabled(true);
    ui->btnCancel->setEnabled(true);

    ui->ManualButton->repaint();

    m.setMode(1);
}

void MainWindow::on_btnMap_clicked()
{
    map->mapDisplay();
    map->show();
}

void MainWindow::on_comboDisplayLine_currentIndexChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        return;
    }
    CTCRouteStatus *temp;
    temp = ctcmap.getRouteStatus(arg1.toStdString());
    ui->blockDisplay->setRoute(temp);

    TrackModel::Route *rte;
    rte = TrackModel::getRoute(arg1.toStdString());

    for(auto &blk : rte->blocks){
        if(blk.second->id != 0){
             ui->comboDisplayBlock->addItem(QString::number(blk.second->id));
        }
    }
}

void MainWindow::updateRoute(){
    for(auto& rte : TrackModel::routes){
        ui->comboDisplayLine->addItem(QString::fromStdString(rte->name));
        ui->comboLine->addItem(QString::fromStdString(rte->name));
    }
}

void MainWindow::on_btnSchedule_clicked()
{
    if(!autoSchedule){
        autoSchedule = new schedule(this);
    }
    autoSchedule->show();
}

void MainWindow::timerEvent(QTimerEvent *event){
    CTCSignals c;
    ctc.dispatch(c);
    killTimer(timerID);
}

void MainWindow::on_btnMaintenance_clicked()
{
    maint->show();
}

void MainWindow::on_comboDisplayBlock_currentIndexChanged(const QString &arg1)
{

    ui->lblBlockOcc->setText("NO");
}

void MainWindow::on_btnThroughput_clicked()
{
    th->show();
}
