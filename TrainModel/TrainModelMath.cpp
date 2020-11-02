#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include <chrono>

TrainModelMath::TrainModelMath(int newNumCars, TrainModelUpdateBlock *newAssigBlock){    
    numCars = newNumCars;
    mass = numCars * 56700;
    block = newAssigBlock;

    currVel = 0;
    currPower = 0;
    currForce = 0;
    currAccel = 0;
    lastVel = 0;
    lastAccel = 0;
    lastPos = 0;
    elapsedTime = 0;
    failureStatus = 0;
    safeStoppingDist = 10;
    inYard = true;
    newBlock = false;
}

void TrainModelMath::setPower(double newPower){
    //Calculate Force from power
    currForce = newPower/lastVel;
    limitForce();

    //Find acceleration from force
    currAccel = currForce/mass;
    limitAccel();

    //Find the current velocity
    currVel = calcVelocity();

    //Get current time
    if (!inYard){
        newTime = systemClock->currentTime();

        //Find elapsed time and convert to a double
        qint64 change;
        change = lastTime.msecsTo(newTime);
        elapsedTime = (double)change;
        lastTime = newTime;

        //Find the distance travelled using old velocity
        double distTravelled = travelledDist(elapsedTime, currVel);
        double newPos = updatePosition(lastPos, distTravelled);

        //compare new position to old to see if new block
        if (newPos >= block->blockDist && block->blockNum<=9){
            newPos = newPos - (block->blockDist);
            //update current block and information
            block->updateTrackInfo(inYard);
        }
        lastPos = newPos;
        lastAccel = currAccel;
        lastVel = currVel;
        currPower = newPower;
    }
    if (inYard && newPower!=0){
        lastTime = systemClock->currentTime();
        lastPos = 0;
        block->updateTrackInfo(inYard);
        inYard = false;
        currVel = calcVelocity();
        lastAccel = currAccel;
        lastVel = currVel;
        currPower = newPower;
    }
}

double TrainModelMath::travelledDist(double time, double velocity) {
    double totalVel = lastVel + currVel;
    double dist = lastPos + ((elapsedTime/2)*totalVel);
    return dist;
}

double TrainModelMath::updatePosition(double oldPos, double change) {
    return oldPos+change;
}

double TrainModelMath::calcVelocity() {
    double totalAcc = lastAccel + currAccel;
    double vel = lastVel + ((elapsedTime/2)*totalAcc);
    return vel;
}

void TrainModelMath::limitForce(){
    if (currForce > (mass*0.5)){
        currForce = mass*0.5;
    }
}

void TrainModelMath::limitAccel(){
    if (currForce == 0 & currVel>0){
        currAccel = -1.2;
    }
    else if (currForce != 0){
        if (currAccel > 0.5){
            currAccel = 0.5;
        }
    }
    else{
        currAccel = 0;
    }
}

void TrainModelMath::setFailureStatus(int newFailureStatus){
    failureStatus = newFailureStatus;
}

int TrainModelMath::getFailureStatus(){
    return failureStatus;
}
