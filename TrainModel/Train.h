#ifndef TRAIN_H
#define TRAIN_H
#include "TrainModelUI.h"
#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include <QMainWindow>
#include <chrono>
#include <cstdint>
using namespace std;

class Train
{
public:
    int numCars;
    uint64_t trackCircuitData;
    double power;
    double oldPos;
    chrono::steady_clock::time_point oldTime;
    double currVel;
    double currPower;
    double blockDist = 50;
    double blockGrade = 0;
    int blockNum;


    Train(int newNumCars, int argc, char *argv[]);
    //Train(int, char);
    void setPower(double newPower);             //Called by train controller to set power
    void setTrackCircuit(int blockNum);       //Get curr track signal from Track Model when new block
    uint64_t sendTrackCircuit();                //Train controller can call to get curr track signal
    void updateTrackInfo();                     //Will update block information
    double getCurrentVelocity();                //Called by train controller to get curr velocity
    double getCurrentPosition();                //will return current position
};

#endif // TRAIN_H