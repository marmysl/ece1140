#include "TrainModelUI.h"
#include "ui_TrainModelUI.h"

TrainModelUI::TrainModelUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrainModelUI)
{
    ui->setupUi(this);
}

TrainModelUI::~TrainModelUI()
{
    delete ui;
}

/*void TrainModelUI::updatePower(double power){
    ui->powerLabel->setText(QString::number(power));
}*/
