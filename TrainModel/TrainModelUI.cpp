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

void TrainModelUI::setTrain(TrainModelMath *trainNew){
    train = trainNew;
}

void TrainModelUI::updatePower(double power){
    ui->powerLabel->setText(QString::number(power));
}

void TrainModelUI::updateVelocity(double currVel){
    ui->velLabel->setText(QString::number(currVel*2.237));
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
    QString lightStr = "Off";
    if(lights){lightStr = "On";}
    ui->cabinLightLabel->setText(lightStr);
}

void TrainModelUI::updateTemp(int temp){
    ui->tempLabel->setText(QString::number(temp));
}

void TrainModelUI::updateHeater(bool heat){
    QString heatStr = "Off";
    if(heat){heatStr = "On";}
    ui->heaterLabel->setText(heatStr);
}

void TrainModelUI::updateAC(bool ac){
    QString acStr = "Off";
    if(ac){acStr = "On";}
    ui->acLabel->setText(acStr);
}

void TrainModelUI::updateAds(bool ads){
    QString adsStr = "Off";
    if(ads){adsStr = "On";}
    ui->adLabel->setText(adsStr);
}



void TrainModelUI::on_pushButton_clicked()
{
    train->setEBrake(true);
}
