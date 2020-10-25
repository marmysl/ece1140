#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include <chrono>

TrainModelMath::TrainModelMath(int newNumCars, TrainModelUpdateBlock *newBlock){
    numCars = newNumCars;
    block = newBlock;
}

void TrainModelMath::setPower(double newPower){
    //Get current time
    if (!inYard){
        chrono::steady_clock::time_point newTime= chrono::steady_clock::now();

        //Find elapsed time and convert to a double
        auto elapsedTime = newTime - lastTime;
        lastTime = newTime;
        double milliSec = chrono::duration<double, milli>(elapsedTime).count();

        //Find the distance travelled using old velocity
        double distTravelled = this->travelledDist(milliSec, currVel);
        double newPos = this->updatePosition(lastPos, distTravelled);

        //compare new position to old to see if new block
        if (newPos >= block->blockDist && block->blockNum<=10){
            newPos = newPos - block->blockDist;
            //update current block and information
            block->updateTrackInfo(inYard);
        }
        lastPos = newPos;
        currPower = newPower;
        double newCurrVel = this->calcVelocity(newPower);
        currVel = newCurrVel;
    }
    if (inYard && newPower!=0){
        lastTime = chrono::steady_clock::now();
        lastPos = 0;
        block->updateTrackInfo(inYard);
        //lastTime = chrono::steady_clock::now();
        //lastPos = 0;
        currPower = newPower;
        double newCurrVel = TrainModelMath::calcVelocity(newPower);
        currVel = newCurrVel;
        inYard = false;
    }
}

double TrainModelMath::travelledDist(double time, double velocity) {
    double dist = velocity * time;
    return dist;
}

double TrainModelMath::updatePosition(double oldPos, double change) {
    return oldPos+change;
}

double TrainModelMath::calcVelocity(double power) {
    //return 20;
    return power; //morgen debug
}

void TrainModelMath::calcForce(){

}

void TrainModelMath::getVel(){

}

void TrainModelMath::setFailureStatus(int newFailureStatus){
    failureStatus = newFailureStatus;
}

int TrainModelMath::getFailureStatus(){
    return failureStatus;
}
