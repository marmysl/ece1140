#ifndef TRAINMODELMATH_H
#define TRAINMODELMATH_H
#include <QObject>
#include <QTimer>
#include <QDateTime>
#include "timetracker.h"
#include "TrainModelUpdateBlock.h"

using namespace std;

class TrainModelMath
{
public:
    int numCars = 3;
    double currVel = 0;
    double currPower = 0;
    double currForce = 0;
    double currAccel = 0;
    double lastVel = 0;
    double lastAccel = 0;
    double lastPos = 0;
    QDateTime lastTime;
    QDateTime newTime;
    double elapsedTime = 0;
    bool newBlock = false;
    int failureStatus = 0;
    int safeStoppingDist = 10;
    bool inYard = true;
    TrainModelUpdateBlock *block;
    bool emergencyBrake = false;
    bool serviceBrake = false;

    //values that I might decide to make a different class for
    double mass = 0;
    double accel = 0.5;
    double deccSB = 1.2;
    double deccEB = 2.73;

    TrainModelMath(int newNumCars, TrainModelUpdateBlock *block);
    TrainModelMath();
    double travelledDist();
    double calcVelocity();
    void setPower(double);
    void limitForce();
    void limitAccel();
    void setFailureStatus(int);
    int getFailureStatus();
    void setEBrake(bool);
    void setSBrake(bool);
};

#endif // TRAINMODELMATH_H
