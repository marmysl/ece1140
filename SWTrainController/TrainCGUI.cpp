#include "TrainCGUI.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QGeoRoute>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_clicked()
{
    QString temp1,temp2;
    double kp, ki, power;

    //convert input string to text then assign to Kp  & Ki
    temp1 = ui->kp_textbox->toPlainText();
    kp = temp1.toDouble();
    temp2 =  ui->ki_textbox->toPlainText();
    ki = temp2.toDouble();

    // Clear textboxes
    ui->ki_textbox->clear();
    ui->kp_textbox->clear();

    // set Power = Kp + Ki, then display on UI
    power = kp + ki;
    ui->p_out_label->setText(QString::number(power));

}


