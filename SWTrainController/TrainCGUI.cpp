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

/* Every timer event (1 second), update info about the train */
void TrainControlWindow::timerEvent(QTimerEvent *event)
{
    count++;
    std::cout << "Timer has updated... " << count << std::endl; //debug

    swtc.setTrainVelocity(train->getCurrentVelocity()); //gets the current speed of the train
    ui->currspeed_->setText(QString::number(swtc.getTrainVelocity()));
   // std::cout << "SWTC has received the current speed of train. It is " << swtc.getTrainVelocity() << std::endl; //debug

    train->setPower(swtc.getPowerCommand()); //feeds train new power every sec
    ui->powerOutput_->setText(QString::number(swtc.getPowerCommand()));
    //std::cout << "SWTC has sent power command to train. It is " << swtc.getPowerCommand() << std::endl; //debug
}

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

    // Disable textboxes (Kp and Ki are only set at dispatch)
    ui->ki_textbox->setReadOnly(true);
    ui->kp_textbox->setReadOnly(true);

    cout << "Kp and Ki have been set." << std::endl; //debug

    //Calculate the initial power for the yard speed (5 m/s)
    int newpower = swtc.calculatePower(5.0);
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

void TrainControlWindow::on_getCircuitInfoButton_clicked()
{
    // signal = train.sendTrackCircuit();

}

/* Slowly reduces the power commanded by calculating a new
 * power using the train's current velocity minus the decel rate,
 * until the train model's current velocity is 0 m/s */
void TrainControlWindow::on_serviceBrake_clicked()
{
    std::cout << "Service brake has been applied.\n"; //debug

    /*while (swtc.getTrainVelocity() != 0)
    {
        // service brake decel = 1.2 m/s^2, currently running at 1s
        swtc.setPowerCommand(swtc.calculatePower(swtc.getTrainVelocity() - 1.2));
    }*/
}
