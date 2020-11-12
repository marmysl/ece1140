#include "Train.h"
#include <QApplication>
#include <cstdint>
#include <iostream>

#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include "TrainModelControls.h"

using namespace std;

Train::Train(int newNumCars, string lineType)
{
    w = new TrainModelUI();
    w->show();
    controls = new TrainModelControls();
    block = new TrainModelUpdateBlock(lineType);
    math = new TrainModelMath(newNumCars, block);
    w->setTrain(math);
    updateUI();
}

void Train::setPower(double newPower){             //Called by train controller to set power
    math->setPower(newPower);
    updateUI();
}

uint64_t Train::sendTrackCircuit(){
    return block->trackCircuitData;
}

double Train::getCurrentVelocity(){
    return math->currVel;
}

void Train::setDoorStatus(bool doorStatus){
    controls->toggleDoor(doorStatus);
    w->updateDoors(controls->doorOpen);
}

bool Train::getDoorStatus(){
    return controls->doorOpen;
}

void Train::setLeftDoorStatus(bool doorStatus){
    controls->toggleLeftDoor(doorStatus);
    //w->updateDoors(controls->doorOpen);
}

bool Train::getLeftDoorStatus(){
    return controls->doorOpen;
}

void Train::setRightDoorStatus(bool doorStatus){
    controls->toggleRightDoor(doorStatus);
    //w->updateDoors(controls->doorOpen);
}

bool Train::getRightDoorStatus(){
    return controls->doorOpen;
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
    controls->setTemp(newTemp);
    w->updateTemp(controls->getTemp());
}

double Train::getTemp(){
    return controls->temp;
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
    controls->setAnn(annString);
}

bool Train::getAnnouncements(){
    return controls->announcementsOn;
}

uint64_t Train::getBeaconData(){
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
    w->updatePower(math->currPower);
    w->updateVelocity(math->currVel);
    w->updateBlockNum(block->blockNum);
    w->updateBlockLength(block->blockDist);
    w->updateBlockGrade(block->blockGrade);
}

