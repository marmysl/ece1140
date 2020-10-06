#ifndef TRAIN_H
#define TRAIN_H
#include "TrainModelUI.h"
#include <QMainWindow>
using namespace std;

class Train
{
public:
    int numCars;
    uint16_t trackCircuitData;
    double power;
    double oldPos;
    chrono::steady_clock::time_point oldTime;
    double currVel;
    double currPower;
    double blockDist = 50;
    int currBlock;

    Train(int, int, char **);
    //Train(int, char);
    void setPower(double newPower);             //Called by train controller to set power
    void getTrackCircuit(int block);       //Get curr track signal from Track Model when new block
    uint16_t sendTrackCircuit();                //Train controller can call to get curr track signal
    void updateTrackInfo();                     //Will update block information
    double getCurrentVelocity();                //Called by train controller to get curr velocity
    double getCurrentPosition();                //will return current position
};

#endif // TRAIN_H
