/**
 * This class handles the UI and UI updates. It updates all labels in the UI and handles any button action.
 *
 * QTCreator was used initially to set up the UI.
*/
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

void TrainModelUI::setLength(double length){
    ui->lengthLabel->setText(QString::number(length));
}

void TrainModelUI::setMass(double weight){
    ui->massLabel->setText(QString::number(weight/1016));
}

void TrainModelUI::updatePower(double power){
    ui->powerLabel->setText(QString::number(power));
}

void TrainModelUI::updateVelocity(double currVel){
    ui->velLabel->setText(QString::number(currVel*2.237));
}

void TrainModelUI::updateAccel(double currAccel){
    ui->accelLabel->setText(QString::number(currAccel*3.281));
}

void TrainModelUI::updateForce(double currForce){
    ui->forceLabel->setText(QString::number(currForce));
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

void TrainModelUI::updateLeftDoors(bool door){
    QString doorStr = "Closed";
    if(door){doorStr = "Open";}
    ui->doorLabelLeft->setText(doorStr);
}

void TrainModelUI::updateRightDoors(bool door){
    QString doorStr = "Closed";
    if(door){doorStr = "Open";}
    ui->doorLabelRight->setText(doorStr);
}

void TrainModelUI::updateCabinLights(bool lights){
    QString lightStr = "Off";
    if(lights){lightStr = "On";}
    ui->cabinLightLabel->setText(lightStr);
}

void TrainModelUI::updateHeadLights(bool lights){
    QString lightStr = "Off";
    if(lights){lightStr = "On";}
    ui->headlightLabel->setText(lightStr);
}

void TrainModelUI::updateTemp(int temp){
    ui->tempLabel->setText(QString::number(temp));
    ui->setTempLabel->setText(QString::number(train->setTemp));
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

void TrainModelUI::updateFailureStatus(){
    QString goesIn = "Status will appear here";
    if(train->emergencyBrake){goesIn = "Emergency Brake Pulled";}
    else if(train->getFailureStatus()==1){goesIn = "Signal Pickup Failure";}
    else if(train->getFailureStatus()==2){goesIn = "Engine Failure";}
    else if(train->getFailureStatus()==3){goesIn = "Brake Failure";}
    ui->failStatus->setText(goesIn);
}

void TrainModelUI::updateAnnouncements(std::string str){
    QString announce = QString::fromStdString(str);
    ui->announceL->setText(announce);
}

void TrainModelUI::updatePassengers(int numPass, int depart, int board){
    ui->passengerLabel->setText(QString::number(numPass));
    ui->departedLabel->setText(QString::number(depart));
    ui->boardedLabel->setText(QString::number(board));
}

void TrainModelUI::on_pushButton_clicked()
{
    train->setEBrake(true);
}

void TrainModelUI::on_pushButton_2_clicked()
{
    train->setFailureStatus(1);
}

void TrainModelUI::on_pushButton_3_clicked()
{
    train->setFailureStatus(2);
}

void TrainModelUI::on_pushButton_4_clicked()
{
    train->setFailureStatus(3);
}

void TrainModelUI::on_pushButton_5_clicked()
{
    //limit the set temp to have a max of 85
    if((train->setTemp)<85){
        train->setTemperature((train->setTemp)+1);
    }
}

void TrainModelUI::on_pushButton_6_clicked()
{
    //limit the set temp to have a min of 60
    if((train->setTemp)>60){
        train->setTemperature((train->setTemp)-1);
    }
}
