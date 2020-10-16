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

    timerID = startTimer(1000);
    count = 0;
}

TrainControlWindow::~TrainControlWindow()
{
    killTimer(timerID);
    delete ui;
}

void TrainControlWindow::timerEvent(QTimerEvent *event)
{
    count++;
    std::cout << "Timer has updated... Count is " << count << std::endl;
}

void TrainControlWindow::on_submit_clicked() // on "Submit" the controller instantiates a Train class
{
    //convert input string to text then assign to Kp  & Ki [kinda useless]
    QString temp1,temp2;
    temp1 = ui->kp_textbox->toPlainText();
    kp = temp1.toDouble();
    temp2 =  ui->ki_textbox->toPlainText();
    ki = temp2.toDouble();

    // Clear textboxes
    ui->ki_textbox->clear();
    ui->kp_textbox->clear();

    // [temporary, for iteration 2] set Power = Kp + Ki, then display on UI
    power = kp + ki;
    ui->p_out_label->setText(QString::number(power));

}

void TrainControlWindow::on_sendPowerButton_clicked() // Currently a button, but will need to be a loop.
{
    std::cout << "Setting power...\n";

    train->setPower(power);

    std::cout << "Power sent.\n";
    //std::cout << "The velocity is " << train->getCurrentVelocity() << endl;

    double testytest = train->getCurrentVelocity();
    ui->currspeed_->setText(QString::number(testytest));
}

void TrainControlWindow::on_getCircuitInfoButton_clicked()
{
    // signal = train.sendTrackCircuit();

}
