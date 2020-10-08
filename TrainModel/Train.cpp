#include "Train.h"
#include <QApplication>
#include <chrono>
#include <cstdint>

#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
using namespace std;

Train::Train(int newNumCars, int argc, char *argv[])
{
    numCars = newNumCars;
    QApplication a(argc, argv);
    TrainModelUI w;
    uiPtr = &w;
    qapp = &a;
    w.show();
    updateUI();
    a.exec();
}

void Train::setPower(double newPower){             //Called by train controller to set power
    //Get current time
    chrono::steady_clock::time_point newTime= chrono::steady_clock::now();

    //Find elapsed time and convert to a double
    auto elapsedTime = newTime - oldTime;
    oldTime = newTime;
    double milliSec = chrono::duration<double, milli>(elapsedTime).count();

    //Find the distance travelled using old velocity
    double distTravelled = TrainModelMath::travelledDist(milliSec, currVel);
    double newPos = TrainModelMath::updatePosition(oldPos, distTravelled);

    //compare new position to old to see if new block
    if (newPos >= blockDist){
        newPos = newPos - blockDist;
        //update current block and information
        this->updateTrackInfo();
    }
    oldPos = newPos;
    updateUI();
    currPower = newPower;
    double newCurrVel = TrainModelMath::calcVelocity(newPower);
    currVel = newCurrVel;
}

void Train::updateTrackInfo(){                            //Will update block information
    //update block num
    //update block length
    //send occupancy to Track Model
    blockNum = TrainModelUpdateBlock::updateBlock(blockNum);
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
 /*   uiPtr->updateNumCars(numCars);
    uiPtr->updatePower(power);
    uiPtr->updateVelocity(currVel);
    uiPtr->updateVelocity(currVel);
    uiPtr->updateBlockNum(blockNum);
    uiPtr->updateBlockLength(blockDist);
    uiPtr->updateBlockGrade(blockGrade);    */
}
