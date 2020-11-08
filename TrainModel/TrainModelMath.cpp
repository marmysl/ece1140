#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include <iostream>

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
    currPower = newPower;

    //Calculate Force from Power input
    currForce = newPower/lastVel;
    limitForce();

    //Find acceleration from calculated force
    currAccel = currForce/mass;
    limitAccel();

    //Get current time, don't use last time until out of yard
    if (!inYard){
        newTime = systemClock->currentTime();

        //Find elapsed time and convert to a double
        qint64 change;
        change = lastTime.msecsTo(newTime);
        elapsedTime = (double)change/1000;
        lastTime = newTime;

        //Find the current velocity
        currVel = calcVelocity();

        //Find the distance travelled using old velocity
        double newPos = travelledDist();

        //compare new position to old to see if new block
        if (newPos >= block->blockDist && block->blockNum<=9){
            newPos = newPos - (block->blockDist);
            //update current block and information
            block->updateTrackInfo(inYard);
        }

        //Set current calculations as last calculations for next call
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

double TrainModelMath::travelledDist() {
    double totalVel = lastVel + currVel;
    double dist = lastPos + ((elapsedTime/2)*totalVel);
    return dist;
}

double TrainModelMath::calcVelocity() {
    double totalAcc = lastAccel + currAccel;
    double vel = lastVel + ((elapsedTime/2)*totalAcc);

    if (vel < 0){ vel=0; }

    if (lastVel <= 0 && (serviceBrake || emergencyBrake)){ vel=0; }

    return vel;
}

void TrainModelMath::limitForce(){
    if (currForce > (mass*0.5)){
        currForce = mass*0.5;
    }
    else if (currPower == 0 && lastVel == 0){
        currForce = 0;
    }
    else if (lastVel == 0){
        currForce = mass*0.5;
    }
}

void TrainModelMath::limitAccel(){
    if (currForce == 0 & currVel>0){
        if(emergencyBrake){currAccel = -2.73;}
        else{currAccel = -1.2;}
    }
    else if (currForce != 0){
        if (currAccel > 0.5){currAccel = 0.5;}
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

void TrainModelMath::setEBrake(bool status){
    emergencyBrake = status;
}

void TrainModelMath::setSBrake(bool status){
    serviceBrake = status;
}
