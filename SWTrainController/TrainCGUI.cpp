//  Implementation file for SW Train Controller GUI

#include "TrainCGUI.h"
#include "TrainController.h"
#include "ui_TrainController.h"
// #include  "Train.h" // Leaving as comment until Train.h exists

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

    // Initialize a train class
    int numofCars = 3; //hard coding number of traincars for now - we will see what to do with this eventually
    //Train* train = new Train(numofCars, argc, argv);
}

void MainWindow::on_sendPowerButton_clicked() // Currently a button, but will need to be a loop.
{
    // How to use train object here if it's initialized in an earlier function locally?
    // train.setPower(power);
}

void MainWindow::on_getCircuitInfoButton_clicked()
{
    // signal = train.sendTrackCircuit();

}
