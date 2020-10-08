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

void TrainModelUI::updatePower(double power){
    ui->powerLabel->setText(QString::number(power));
}

void TrainModelUI::updateVelocity(double currVel){
    ui->velLabel->setText(QString::number(currVel));
}

void TrainModelUI::updateBlockNum(int block){
    ui->blockNumLabel->setText(QString::number(block));
}

void TrainModelUI::updateBlockLength(double length){
    ui->blockLengthLabel->setText(QString::number(length));
}

void TrainModelUI::updateBlockGrade(double grade){
    ui->blockGradeLabel->setText(QString::number(grade));
}

void TrainModelUI::updateNumCars(int cars){
    ui->numCarLabel->setText(QString::number(cars));
}
