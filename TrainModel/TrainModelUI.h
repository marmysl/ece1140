#ifndef TRAINMODELUI_H
#define TRAINMODELUI_H
#include "TrainModelMath.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TrainModelUI; }
QT_END_NAMESPACE

class TrainModelUI : public QMainWindow
{
    Q_OBJECT

public:
    TrainModelMath *train;
    TrainModelUI(QWidget *parent = nullptr);
    ~TrainModelUI();
    void setTrain(TrainModelMath *trainNew);
    void setLength(double length);
    void setMass(double);
    void updatePower(double power);
    void updateVelocity(double currVel);
    void updateBlockNum(int block);
    void updateBlockLength(double length);
    void updateBlockGrade(double grade);
    void updateNumCars(int cars);
    void updateLeftDoors(bool);
    void updateRightDoors(bool);
    void updateHeadLights(bool);
    void updateCabinLights(bool);
    void updateTemp(int);
    void updateHeater(bool);
    void updateAC(bool);
    void updateAds(bool);
    void updateFailureStatus();
    void updateAnnouncements(std::string);
    void updatePassengers(int, int, int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::TrainModelUI *ui;
};
#endif // TRAINMODELUI_H
