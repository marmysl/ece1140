#ifndef TRAINCONTROLWINDOW_H
#define TRAINCONTROLWINDOW_H

#include <QMainWindow>

#include "SWTrainController_main.h"
#include "SWTC.h"
#include "TrainModel/Train.h"
#include "ui_SWTrainController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TrainControlWindow; }
QT_END_NAMESPACE

class TrainControlWindow : public QMainWindow
{
    Q_OBJECT


public:
    TrainControlWindow(QWidget *parent = nullptr);
    ~TrainControlWindow();
    Train* train;
    SWTC swtc;
    double temp = 5.0;
    double yardSpeed = 5.0; //speed of train in yard before block 1

    void updateCircuitInfo();
    void updatePower();
    void updateBrakes();

private slots:
    void on_submit_clicked();
    void on_sendPowerButton_clicked();
    void on_getCircuitInfoButton_clicked();

    void on_serviceBrake_clicked();

    void on_emergencyBrake_clicked();

private:
    Ui::TrainControlWindow *ui;
    int timerID;
    int count; //debug

    double power; //remove someday
    double kp;
    double ki;
    int argc;
    char *argv[];

protected:
    void timerEvent(QTimerEvent *event);

};
#endif // TRAINCONTROLWINDOW_H
