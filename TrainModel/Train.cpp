#include "Train.h"
#include <QApplication>
#include <cstdint>
#include <iostream>

#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include "TrainModelControls.h"
#include "../TrackModel/trackmodel_types.hpp"

using namespace std;

Train::Train(int newNumCars, string lineType)
{
    w = new TrainModelUI();
    w->show();
    controls = new TrainModelControls();
    block = new TrainModelUpdateBlock(lineType);
    math = new TrainModelMath(newNumCars, block, controls);
    w->setTrain(math);
    updateUI();
}

void Train::setPower(double newPower){             //Called by train controller to set power
    math->setPower(newPower);
    updateUI();
}

double Train::getPower() {
    return math->currPower;
}

uint64_t Train::sendTrackCircuit(){
    // Return track circuit data of current block. If signal pickup failure, return 0xFFFFFFFFFFFFFFFF
    if(math->getFailureStatus()==1){
        return 0xFFFFFFFFFFFFFFFF;
    }
    return block->trackCircuitData;
    //return 0x0002000000000032;
}

double Train::getCurrentVelocity(){
    return math->currVel;
}

void Train::setDoorStatus(bool doorStatus){
    controls->toggleLeftDoor(doorStatus);
    w->updateLeftDoors(controls->doorLeftOpen);
}

bool Train::getDoorStatus(){
    return controls->doorLeftOpen;
}

void Train::setLeftDoorStatus(bool doorStatus){
    controls->toggleLeftDoor(doorStatus);
    w->updateLeftDoors(controls->doorLeftOpen);
}

bool Train::getLeftDoorStatus(){
    return controls->doorLeftOpen;
}

void Train::setRightDoorStatus(bool doorStatus){
    controls->toggleRightDoor(doorStatus);
    w->updateRightDoors(controls->doorRightOpen);
}

bool Train::getRightDoorStatus(){
    return controls->doorRightOpen;
}

void Train::setCabinLights(bool lightStatus){
    controls->toggleCabinLights(lightStatus);
    w->updateCabinLights(controls->cabinLights);
}

bool Train::getCabinLights(){
    return controls->cabinLights;
}

void Train::setHeadlights(bool headlightStatus){
    controls->toggleHeadlights(headlightStatus);
}

bool Train::getHeadlights(){
    return controls->headlightsOn;
}

void Train::setPassengerEBrake(bool passBrake){
    math->setEBrake(passBrake);
}

bool Train::getPassengerEBrake(){
    return math->emergencyBrake;
}

void Train::setEmergencyBrake(bool eBrakeStatus){
    math->setEBrake(eBrakeStatus);
}

bool Train::getEmergencyBrake(){
    return math->emergencyBrake;
}

void Train::setSystemFailure(int failStat){
    math->setFailureStatus(failStat);
}

int Train::getSystemFailure(){
    return math->failureStatus;
}

void Train::setServiceBrake(bool servBrake){
    math->setSBrake(servBrake);
}

bool Train::getServiceBrake(){
    return math->serviceBrake;
}

void Train::setTemp(int newTemp){
    math->setTemperature(newTemp);
    w->updateTemp(math->currTemp);
}

double Train::getTemp(){
    return math->currTemp;
}

void Train::setAC(bool acStatus){
    controls->toggleAC(acStatus);
}

bool Train::getAC(){
    return controls->acOn;
    w->updateAC(controls->acOn);
}

void Train::setHeater(bool heaterStatus){
    controls->toggleHeater(heaterStatus);
    w->updateHeater(controls->heaterOn);
}

bool Train::getHeater(){
    return controls->heaterOn;
}

void Train::setAdvertisements(bool adStatus){
    controls->toggleAdvertisments(adStatus);
    w->updateAds(controls->advertisementsOn);
}

bool Train::getAdvertisements(){
    return controls->advertisementsOn;
}

void Train::setAnnouncements(bool annStatus, string annString){
    controls->toggleAnnouncements(annStatus);
    if(!(controls->announcementsOn)){
        controls->setAnn(" ");
    }
    controls->setAnn(annString);
    w->updateAnnouncements(annString);
}

bool Train::getAnnouncements(){
    return controls->announcementsOn;
}

TrackModel::BeaconData Train::getBeaconData(){
    return block->beaconData;
}

string Train::getAnnouncementMsg(){
    return controls->announcements;
}

double Train::getSafeStoppingDistance(){
    return math->safeStoppingDist;
}

void Train::updateUI(){
    w->updateNumCars(math->numCars);
    w->setLength(math->length);
    w->setMass(math->mass);
    w->updatePower(math->currPower);
    w->updateVelocity(math->currVel);
    w->updateForce(math->currForce);
    w->updateAccel(math->currAccel);
    w->updateBlockNum(block->blockNum);
    w->updateBlockLength(block->blockDist);
    w->updateBlockGrade(block->blockGrade);
    w->updateFailureStatus();
    w->updatePassengers(math->passengers, math->passengersDepart, math->passengersBoard);
    w->updateAC(controls->acOn);
    w->updateHeater(controls->heaterOn);
    w->updateTemp(math->currTemp);
}

