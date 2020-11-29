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

    timerID = startTimer(100);
    count = 0;

    swtc.mode = mode;

    ui->releasebrakebutton->hide();

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

    swtc.mode = mode;

    if (dispatched == false){ // only runs once. checks if mode is automatic, and if it is, then starts a train
        dispatch();
    }

    swtc.readBeacon(train->getBeaconData());
    swtc.calculatePower();
    updatePower();
    updateCircuitInfo();
    updateBrakes();
    updateSpeed();
    updateCabin();
}

// -------------------------------------------------------------------------------- Transmitter update functions
void TrainControlWindow :: updateCircuitInfo()
{
    swtc.decode(train->sendTrackCircuit());
    ui->commspeed_->setText(QString::number(swtc.getCommandedSpeed()*2.237));
    ui->authority_->setText(QString::number(swtc.getAuthority()));

    if (swtc.mode -> getMode() == true) {
        ui->mode_->setText("MODE: MANUAL");
    } else if (swtc.mode->getMode() == false) {
        ui->mode_->setText("MODE: AUTOMATIC");
    } else {
        ui->mode_->setText("MODE: ?");
    }

    // Displays for train stopping due to authority
    if (swtc.getAuthority() == 0) {
        ui->auth_exceeded_->setText("STOPPING! The train has zero authority.");
    } else if (swtc.getAuthority() == 1) {
        ui->auth_exceeded_->setText("Train is slowing due to authority.");
    } else {
        ui->auth_exceeded_->setText("");
    }


    // Display next station


    // Displays for train stopping at station
    if (swtc.getStationUpcoming() == true){
        ui->station_->setText("The train is approaching a station.");
    } else if (swtc.getStationHere() == true && swtc.getTrainVelocity() != 0.0 && swtc.getHasStopped() == false) {
        ui->station_->setText("The train is stopping at a station.");
    } else if (swtc.getStationHere() == true && swtc.getTrainVelocity() == 0.0){
        ui->station_->setText("The train is stopped at a station.");
    } else if (swtc.getStationHere() == true && swtc.getTrainVelocity() != 0.0 && swtc.getHasStopped() == true){
        ui->station_->setText("The train is leaving a station.");
    } else {
        ui->station_->setText("");
    }


}

void TrainControlWindow :: updatePower()
{
    swtc.setTrainVelocity(train->getCurrentVelocity());
    ui->currspeed_->setText(QString::number(swtc.getTrainVelocity()*2.237));

    train->setPower(swtc.getPowerCommand());
    ui->powerOutput_->setText(QString::number(swtc.getPowerCommand() / 1000));
}

void TrainControlWindow :: updateBrakes()  // Update brake flags in train model
{

    // The brakesReleased flag is true when the brakes have just been released by the driver.

    if (brakesReleased == false && train->getPassengerEBrake() == true){  // Checks for a newly applied passenger ebrake
        swtc.setPassengerEBrake(train->getPassengerEBrake());
    } else if (brakesReleased == true && train->getPassengerEBrake() == true){ // Checks if the train flag needs reset
        train->setPassengerEBrake(swtc.getPassengerEBrake());
    }

    if(swtc.getPassengerEBrake() == true){
        swtc.setPowerCommand(0.0);
    }

    // Set each brake
    train->setServiceBrake(swtc.getServiceBrakeFlag());
    train->setEmergencyBrake(swtc.getEmergencyBrakeFlag());
    train->setPassengerEBrake(swtc.getPassengerEBrake());


    // Reset the brakesReleased flag each cycle
    brakesReleased = false;


    // if the train is actively braking, display on GUI for driver
    if (swtc.getEmergencyBrakeFlag() == true){
        ui->releasebrakebutton->show();
        ui->sbrake_->setText("The emergency brake is enabled!");
    } else if (swtc.getServiceBrakeFlag() == true){
        ui->releasebrakebutton->show();
        ui->sbrake_->setText("The service brake is enabled!");
    } else if (swtc.getPassengerEBrake() == true){
        ui->releasebrakebutton->show();
        ui->sbrake_->setText("The passenger e-brake is enabled!");
    } else {
        ui->sbrake_->setText("");
    }
}

void TrainControlWindow :: updateSpeed()
{
    ui->setpointSpeed_->setText(QString::number(swtc.getSetpointSpeed()*2.237));

    // if the setpoint speed exceeds the max speed of the train, add UI message
    if (swtc.getSetpointSpeed() > 19.4444){
        ui->setpointexceeds_->setText("Setpoint exceeds max train speed!");
    } else {
        ui->setpointexceeds_->setText("");
    }
}

void TrainControlWindow :: updateCabin()
{
    // Update current status of the cabin
    QString doors, lights, headlights;

    doors = (train->getDoorStatus()) ? "OPEN" : "CLOSED";

    lights = (train->getCabinLights()) ? "ON" : "OFF";

    headlights = (train->getHeadlights()) ? "ON" : "OFF";

    ui->doors_->setText(doors);
    ui->lights_->setText(lights);
    ui->headlights_->setText(headlights);


    // Send updates to the train, if needed
    train->setDoorStatus(swtc.getDoorsOpen());
    train->setCabinLights(swtc.getCabinLightsOn());
    train->setHeadlights(swtc.getHeadlightsOn());

}

void TrainControlWindow :: dispatch() // only runs once, at dispatch.
{
    if (swtc.mode->getMode() == 0){ // If the train is in automatic mode, set Kp and Ki to default and setpoint = commanded
        swtc.setKi(225 * 1000);
        swtc.setKp(225 * 1000);
        startMoving();
    }

    dispatched = true;
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

    //set Kp and Ki in the SWTC class, multiply by 1000 for tuning
    swtc.setKp(kp * 1000);
    swtc.setKi(ki * 1000);

    startMoving();
}

void TrainControlWindow::startMoving()
{
    // Display values in textboxes
    ui->ki_textbox->setPlainText(QString::number(swtc.getKi() / 1000));
    ui->kp_textbox->setPlainText(QString::number(swtc.getKp() / 1000));

    // Disable textboxes and submit button
    ui->ki_textbox->setReadOnly(true);
    ui->kp_textbox->setReadOnly(true);
    ui->submit->hide();

    cout << "Kp and Ki have been set." << std::endl; //debug

    //Disable service brake flag once Kp and Ki are set
    swtc.setServiceBrake(false);

    // Remove recommended Kp/Ki from UI
    ui->k_rec_->setText("");

    swtc.calculatePower();
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

void TrainControlWindow::on_inc_setspeed_clicked()
{
    double current = swtc.getSetpointSpeed();
    swtc.setSetpointSpeed(current + 5.0);
}

void TrainControlWindow::on_dec_setspeed_clicked()
{
    double current = swtc.getSetpointSpeed();
    swtc.setSetpointSpeed(current - 5.0);
}

void TrainControlWindow::on_door_button_clicked()
{
    swtc.setDoorsOpen(!swtc.getDoorsOpen());
}

void TrainControlWindow::on_lights_button_clicked()
{
    swtc.setCabinLightsOn(!swtc.getCabinLightsOn());
}

void TrainControlWindow::on_headlights_button_clicked()
{
    swtc.setHeadlightsOn(!swtc.getHeadlightsOn());
}

void TrainControlWindow::on_releasebrakebutton_clicked()
{
    swtc.setServiceBrake(false);
    swtc.setEmergencyBrake(false);
    swtc.setPassengerEBrake(false);

    brakesReleased = true; // A flag to indicate the brakes have been released
    // fixes passenger e-brake latching

    ui->releasebrakebutton->hide();
}

