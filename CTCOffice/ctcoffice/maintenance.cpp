#include "maintenance.h"
#include "ui_maintenance.h"

#include "mainwindow.h"

maintenance::maintenance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maintenance)
{
    ui->setupUi(this);

    for(auto& rte : TrackModel::routes){
        ui->comboLine->addItem(QString::fromStdString(rte->name));
    }

    line = ui->comboLine->currentText().toStdString();

    TrackModel::Route *rte;
    rte = TrackModel::getRoute(line);

    for(auto &blk : rte->blocks){
        if(blk.second->id != 0){
             ui->comboBlocks->addItem(QString::number(blk.second->id));
        }
    }

    mm = false;

    ui->lblMainStatus->setText("OFF");

}

maintenance::~maintenance()
{
    delete ui;
}


void maintenance::on_btnMM_clicked()
{
    mm = !mm;

    if(mm == true){
        ui->lblMainStatus->setText("ON");
        //send Track Controller the command to set switches manually
    }
    else{
        ui->lblMainStatus->setText("OFF");
    }


}

void maintenance::on_comboLine_currentIndexChanged(const QString &arg1)
{
    line = arg1.toStdString();

    TrackModel::Route *rte;
    rte = TrackModel::getRoute(line);

    for(auto &blk : rte->blocks){
        if(blk.second->id != 0){
             ui->comboBlocks->addItem(QString::number(blk.second->id));
        }
    }

}

void maintenance::on_comboBlocks_currentIndexChanged(const QString &arg1)
{
    block = arg1.toInt();
}

void maintenance::on_btnSendM_clicked()
{
    //send Track Controller the line, block to be closed for maintenance
}
