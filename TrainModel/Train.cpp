#include "Train.h"
#include <QApplication>
#include <chrono>
#include <cstdint>
#include <iostream>

#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
using namespace std;

Train::Train(int newNumCars)
{
    cout << "Create new Train Model with " << newNumCars << " cars" << endl;
    numCars = newNumCars;
    w = new TrainModelUI();
    blockNum = 0;
    w->show();
    updateUI();
}

void Train::setPower(double newPower){             //Called by train controller to set power
    //Get current time
    if (!inYard){
        chrono::steady_clock::time_point newTime= chrono::steady_clock::now();

        //Find elapsed time and convert to a double
        auto elapsedTime = newTime - oldTime;
        oldTime = newTime;
        double milliSec = chrono::duration<double, milli>(elapsedTime).count();

        //Find the distance travelled using old velocity
        double distTravelled = TrainModelMath::travelledDist(milliSec, currVel);
        double newPos = TrainModelMath::updatePosition(oldPos, distTravelled);

        //compare new position to old to see if new block
        if (newPos >= blockDist && blockNum<=10){
            newPos = newPos - blockDist;
            //update current block and information
            this->updateTrackInfo();
        }
        oldPos = newPos;
        currPower = newPower;
        updateUI();
        double newCurrVel = TrainModelMath::calcVelocity(newPower);
        currVel = newCurrVel;
    }
    if (inYard && newPower!=0){
        blockNum = 0;
        this->updateTrackInfo();
        oldTime = chrono::steady_clock::now();
        oldPos = 0;
        currPower = newPower;
        updateUI();
        double newCurrVel = TrainModelMath::calcVelocity(newPower);
        currVel = newCurrVel;
        inYard = false;
    }
}

void Train::updateTrackInfo(){                            //Will update block information
    //update block num
    //update block length
    //send occupancy to Track Model
    blockNum = TrainModelUpdateBlock::updateBlock(blockNum, inYard);
    blockDist = TrainModelUpdateBlock::blockLength(blockNum);
    blockGrade = TrainModelUpdateBlock::blockGrade(blockNum);
    updateUI();
    this->setTrackCircuit(blockNum);
}

//ask about this ?
void Train::setTrackCircuit(int blockNum){                   //Get curr track signal from Track Model when new block
    //get tc info for block
    //assign
    trackCircuitData = TrainModelUpdateBlock::updateTrackCircuit(blockNum);
}

uint64_t Train::sendTrackCircuit(){          //Train controller can call to get curr track signal
    return trackCircuitData;
}


double Train::getCurrentVelocity(){                //Called by train controller to get curr velocity
    return currVel;
}

double Train::getCurrentPosition(){                //will return current position
    return oldPos;
}

void Train::updateUI(){
    w->updateNumCars(numCars);
    w->updatePower(currPower);
    w->updateVelocity(currVel);
    w->updateVelocity(currVel);
    w->updateBlockNum(blockNum);
    w->updateBlockLength(blockDist);
    w->updateBlockGrade(blockGrade);
}
