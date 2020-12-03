/**
 * This class handles all math calculations for the train.
*/
#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include "TrainModelControls.h"
#include <iostream>

TrainModelMath::TrainModelMath(int newNumCars, TrainModelUpdateBlock *newAssigBlock, TrainModelControls *newControl){
    numCars = newNumCars;
    mass = numCars * 56700;
    length = numCars * 105.6;
    block = newAssigBlock;
    controls = newControl;
    maxPassTotal = numCars * 222;

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
    emergencyBrake = false;
    serviceBrake = false;

    currTemp = weather->getTempFheit();
}

//Main function
void TrainModelMath::setPower(double newPower){
    //Set the power of the train. If engine failure, power is 0
    if(failureStatus == 2){
        currPower = 0;
    }
    else{
        currPower = newPower;
    }

    //Calculate Force from Power input
    currForce = (currPower/lastVel);
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
        if (newPos >= block->blockDist){
            newPos = newPos - (block->blockDist);
            //update current block and information
            block->updateTrackInfo(inYard);
        }

        //Update passengers on the train
        updatePassengers();

        //Regulate the train temperature
        regulateTemperature();

        //Set current calculations as last calculations for next call
        lastPos = newPos;
        lastAccel = currAccel;
        lastVel = currVel;
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
    else if ((currPower == 0 && lastVel == 0) || emergencyBrake == 1){
        currForce = 0;
    }
    else if (lastVel == 0){
        currForce = mass*0.5;
    }
}

void TrainModelMath::limitAccel(){
    if (failureStatus == 3 && currPower == 0){
        currAccel = (currForce/mass);
    }
    else if (currPower == 0 && currVel>0){
        if(emergencyBrake){currAccel = -2.73;}
        else{currAccel = -1.2;}
    }
    else if (currPower != 0){
        if (currAccel > 0.5){currAccel = 0.5;}
    }
    else{
        currAccel = 0;
    }
}

void TrainModelMath::updatePassengers(){
    //if the doors are open and the train was not at a station in previous loop
    if((controls->doorLeftOpen || controls->doorRightOpen) && !atStation){
        //Set variable so that the passengers are only updated once at a station
        atStation = true;
        //Randomly generate the number of passengers leaving the train
        if (passengers>0){
            passengersDepart = rand() % passengers;
            passengers = passengers - passengersDepart;
        }
        int transMax = maxPassTotal - passengers;
        int randomPassEntry = rand() % transMax;
        passengersBoard = block->getPassengers(randomPassEntry);
        passengers = passengers + passengersBoard;
        mass = (numCars * 56700) + (passengers * 68);
    }
    else if (!(controls->doorLeftOpen) && !(controls->doorRightOpen)){
        atStation = false;
    }
}

void TrainModelMath::regulateTemperature(){
    if(currTemp<setTemp){
        controls->toggleHeater(true);
        controls->toggleAC(false);
        if(tempCounter<30){
            tempCounter = tempCounter + 1;
        }
        else{
            tempCounter = 0;
            currTemp = currTemp + 1;
        }
    }
    else if(currTemp>setTemp){
        controls->toggleHeater(false);
        controls->toggleAC(true);
        if(tempCounter<30){
            tempCounter = tempCounter + 1;
        }
        else{
            tempCounter = 0;
            currTemp = currTemp - 1;
        }
    }
    else{
        tempCounter = 0;
    }
}

void TrainModelMath::setTemperature(double newTemp){
    setTemp = newTemp;
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
