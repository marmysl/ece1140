//  Implementation file for SW Train Controller GUI

#include "TrainCGUI.h"
#include "TrainController.h"
#include "ui_TrainController.h"
#include  "../TrainModel/Train.h"

#include <QString>
#include <QGeoRoute>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Train train(3, argc, argv);
    //trainPtr = &train;
    //Train* train = new Train(3, argc, argv);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_clicked() // on "Submit" the controller instantiates a Train class
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

void MainWindow::on_sendPowerButton_clicked() // Currently a button, but will need to be a loop.
{
    // How to use train object here if it's initialized in an earlier function locally? Pointer?
    train->setPower(power);
    //std::cout << "The velocity is " << train->getCurrentVelocity() << endl;

    double testytest = train->getCurrentVelocity();
    ui->suggested_speed_label->setText(QString::number(testytest));
}

void MainWindow::on_getCircuitInfoButton_clicked()
{
    // signal = train.sendTrackCircuit();

}
