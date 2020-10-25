#ifndef TRAINMODELMATH_H
#define TRAINMODELMATH_H
#include <chrono>
#include "TrainModelUpdateBlock.h"

using namespace std;

class TrainModelMath
{
public:
    int numCars = 3;
    double currVel = 0;
    double currPower = 0;
    double currForce = 0;
    double lastPos = 0;
    chrono::steady_clock::time_point lastTime;
    bool newBlock = false;
    int failureStatus = 0;
    int safeStoppingDist = 10;
    bool inYard = true;
    TrainModelUpdateBlock *block;

    TrainModelMath(int newNumCars, TrainModelUpdateBlock *block);
    TrainModelMath();
    double travelledDist(double time, double velocity);
    double updatePosition(double oldPos, double change);
    double calcVelocity(double power);
    void setPower(double);
    void calcVelocity();
    void updatePosition();
    void travelledDist();
    void calcForce();
    void getVel();
    void setFailureStatus(int);
    int getFailureStatus();
};

#endif // TRAINMODELMATH_H
