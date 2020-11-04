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

void TrainModelUI::updateDoors(bool door){
    QString doorStr = "Closed";
    if(door){doorStr = "Open";}
    ui->doorLabel->setText(doorStr);
}

void TrainModelUI::updateCabinLights(bool lights){
    std::string lightStr = "Off";
    if(lights){std::string lightStr = "On";}
    ui->cabinLightLabel->setText(QString::fromStdString(lightStr));
}

void TrainModelUI::updateTemp(int temp){
    ui->tempLabel->setText(QString::number(temp));
}

void TrainModelUI::updateHeater(bool heat){
    std::string heatStr = "Off";
    if(heat){std::string heatStr = "On";}
    ui->heaterLabel->setText(QString::fromStdString(heatStr));
}

void TrainModelUI::updateAC(bool ac){
    std::string acStr = "Off";
    if(ac){std::string acStr = "On";}
    ui->acLabel->setText(QString::fromStdString(acStr));
}

void TrainModelUI::updateAds(bool ads){
    std::string adsStr = "Off";
    if(ads){std::string adsStr = "On";}
    ui->adLabel->setText(QString::fromStdString(adsStr));
    }
