#include "SWTrackCntrlGUI.h"
#include "ui_SWTrackCntrlGUI.h"

SWTrackCntrlGUI::SWTrackCntrlGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SWTrackCntrlGUI)
{
    ui->setupUi(this);
}

SWTrackCntrlGUI::~SWTrackCntrlGUI()
{
    delete ui;
}

void SWTrackCntrlGUI::setTable() {

    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("0"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("0"));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem("0"));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("0"));
    ui->tableWidget->setItem(1, 2, new QTableWidgetItem("0"));
    ui->tableWidget->setItem(1, 3, new QTableWidgetItem("0"));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem("0"));
    ui->tableWidget->setItem(2, 2, new QTableWidgetItem("0"));
    ui->tableWidget->setItem(2, 3, new QTableWidgetItem("0"));



}
