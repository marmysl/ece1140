#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <../TrainModel/Train.h>
#include "TrainController.h"
#include "ui_TrainController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Train* train;

private slots:
    void on_submit_clicked();
    void on_sendPowerButton_clicked();
    void on_getCircuitInfoButton_clicked();

private:
    Ui::MainWindow *ui;


    double power; //remove someday
    double kp;
    double ki;
    int argc;
    char *argv[];



};
#endif // MAINWINDOW_H
