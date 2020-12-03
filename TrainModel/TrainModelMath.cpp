/**
 * This class handles all math calculations for the train.
 * It occurs when the train controller PID loop is run and sets a new power for the train every loop.
 * All calculations are then made to move the train along the track and account for changing distance,
 * as well as calculate the new current velocity that is grabbed by the train controller for the next PID
 * loop calculation.
*/
#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include "TrainModelControls.h"
#include <iostream>

TrainModelMath::TrainModelMath(int newNumCars, TrainModelUpdateBlock *newAssigBlock, TrainModelControls *newControl){
    //make initial train characterisitic calculations
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

//Main function that is run when the train controller PID loop sets 0
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

    //Get current time, don't use previous time until out of yard
    // Time is based on system clock changes
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
        //While train is in the yard, keep last variables same
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

// calculate the travelled distance of train from last loop
double TrainModelMath::travelledDist() {
    double totalVel = lastVel + currVel;
    double dist = lastPos + ((elapsedTime/2)*totalVel);
    return dist;
}

// calculate average velocity from last loop
double TrainModelMath::calcVelocity() {
    double totalAcc = lastAccel + currAccel;
    double vel = lastVel + ((elapsedTime/2)*totalAcc);

    // limit so that if velocity calculation is less than 0, it is = 0
    // this stops the train from reversing
    if (vel < 0){ vel=0; }
    if (lastVel <= 0 && (serviceBrake || emergencyBrake)){ vel=0; }

    return vel;
}

// limit the force of the train to max characteristic capability
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

// limit acceleration according to what brake is being used and what situation train is in
void TrainModelMath::limitAccel(){
    if (failureStatus == 3 && currPower == 0){  //brake failure
        currAccel = (((currForce) - (0.01*mass*9.8))/mass);
    }
    else if (currPower == 0 && currVel>0){      //service or emergency brake
        if(emergencyBrake){currAccel = -2.73;}
        else{currAccel = -1.2;}
    }
    else if (currPower != 0){                   //normal acceleration limit
        if (currAccel > 0.5){currAccel = 0.5;}
    }
    else{
        currAccel = 0;
    }
}

//function to update the passenger count on the train when at a station
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

        //pick up passengers through track model
        int transMax = maxPassTotal - passengers;
        int randomPassEntry = rand() % transMax;
        passengersBoard = block->getPassengers(randomPassEntry);
        passengers = passengers + passengersBoard;

        //calculate new mass based on passenger count
        mass = (numCars * 56700) + (passengers * 68);
    }
    //reset bool to false when the doors are closed
    else if (!(controls->doorLeftOpen) && !(controls->doorRightOpen)){
        atStation = false;
    }
}

//regulate internal train temperature
void TrainModelMath::regulateTemperature(){
    //turn on the heat if less than set point temp
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
    //turn on AC if greater than set point temp
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
