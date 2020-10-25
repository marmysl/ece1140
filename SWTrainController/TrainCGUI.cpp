//  Implementation file for SW Train Controller GUI

#include "TrainCGUI.h"


#include <QString>
#include <QtLocation/QGeoRoute>
#include <iostream>

TrainControlWindow::TrainControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrainControlWindow)
{
    ui->setupUi(this);

    timerID = startTimer(1000); // timer event occurs every second
    count = 0;
}

TrainControlWindow::~TrainControlWindow()
{
    killTimer(timerID);
    delete ui;
}

// --------------------------------------------------------------------------------- Transmitter
void TrainControlWindow::timerEvent(QTimerEvent *event)
{
    count++;
    //std::cout << "Timer has updated... " << count << std::endl; //debug

    updatePower();
    updateCircuitInfo();
    updateBrakes();
}

// -------------------------------------------------------------------------------- Transmitter update functions
void TrainControlWindow :: updateCircuitInfo()
{
    swtc.decode(train->sendTrackCircuit());
    ui->commspeed_->setText(QString::number(swtc.getCommandedSpeed()));
    ui->authority_->setText(QString::number(swtc.getAuthority()));
}

void TrainControlWindow :: updatePower()
{
    swtc.setTrainVelocity(train->getCurrentVelocity());
    ui->currspeed_->setText(QString::number(swtc.getTrainVelocity()));

    train->setPower(swtc.getPowerCommand());
    ui->powerOutput_->setText(QString::number(swtc.getPowerCommand()));
}

void TrainControlWindow :: updateBrakes()
{
    // if the train is actively braking, display on GUI for driver
    if (swtc.getEmergencyBrakeFlag() == true){
        ui->ebrake_->setText("The emergency brake is enabled!");
    } else {
        ui->ebrake_->setText("");
    }

    if (swtc.getServiceBrakeFlag() == true){
        ui->sbrake_->setText("The service brake is enabled!");
    } else {
        ui->sbrake_->setText("");
    }

    // if the train has 0 velocity, reset the brake flags
    if ((train->getCurrentVelocity()) == 0.0) {
        swtc.setServiceBrake(false);
        swtc.setEmergencyBrake(false);
    }
}

// ------------------------------------------------------------------------------------------- GUI buttons n' stuff
void TrainControlWindow::on_submit_clicked() //Submits Kp and Ki
{
    //convert input string to text then assign to Kp  & Ki
    QString temp1,temp2;
    temp1 = ui->kp_textbox->toPlainText();
    kp = temp1.toDouble();
    temp2 =  ui->ki_textbox->toPlainText();
    ki = temp2.toDouble();

    //set Kp and Ki in the SWTC class for math stuffs later
    swtc.setKp(kp);
    swtc.setKi(ki);

    // Disable textboxes and submit button
    ui->ki_textbox->setReadOnly(true);
    ui->kp_textbox->setReadOnly(true);
    ui->submit->setDisabled(true);

    cout << "Kp and Ki have been set." << std::endl; //debug

    //Calculate the initial power for the yard speed (5 m/s)
    double newpower = swtc.calculatePower(yardSpeed);
    swtc.setPowerCommand(newpower);

    cout << "The initial power for 5m/s has been set by the train controller.\n";

}

void TrainControlWindow::on_sendPowerButton_clicked() // Currently a button, but will need to be a loop.
{
    std::cout << "Setting power command to " << temp << std::endl;

    //power = swtc.calculatePower();
    swtc.setPowerCommand(temp);

    std::cout << "Power command set.\n";

    temp++;
}

void TrainControlWindow::on_serviceBrake_clicked()
{
    std::cout << "Service brake has been applied.\n"; //debug

    swtc.setPowerCommand(0.0); // set power command to zero
    swtc.setServiceBrake(true);
}

void TrainControlWindow::on_emergencyBrake_clicked()
{
    std::cout << "Emergency brake has been applied.\n"; //debug

    swtc.setPowerCommand(0.0); // set power command to zero
    swtc.setEmergencyBrake(true);
}
