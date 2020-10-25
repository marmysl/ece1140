#include "Train.h"
#include <QApplication>
#include <chrono>
#include <cstdint>
#include <iostream>

#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include "TrainModelControls.h"

using namespace std;

Train::Train(int newNumCars)
{
    cout << "Created new Train Model with " << newNumCars << " cars" << endl;
    w = new TrainModelUI();
    cout << "made train ui";
    w->show();
    cout << "show train ui";
    controls = new TrainModelControls();
    cout << "made controls";
    block = new TrainModelUpdateBlock();
    math = new TrainModelMath(newNumCars, block);
    cout << "made math";
    //block = new TrainModelUpdateBlock();
    cout << "made block";
    updateUI();
    cout << "made it to the end of const ";
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
}

bool Train::getDoorStatus(){
    return controls->doorOpen;
}

void Train::setCabinLights(bool lightStatus){
    controls->toggleCabinLights(lightStatus);
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
    emergencyBrake = eBrakeStatus;
}

bool Train::getEmergencyBrake(){
    return emergencyBrake;
}

void Train::setSystemFailure(int failStat){
    math->setFailureStatus(failStat);
}

int Train::getSystemFailure(){
    return math->failureStatus;
}

void Train::setServiceBrake(bool servBrake){
    serviceBrake = servBrake;
}

bool Train::getServiceBrake(){
    return serviceBrake;
}

void Train::setTemp(int newTemp){
    controls->setTemp(newTemp);
}

double Train::getTemp(){
    return controls->temp;
}

void Train::setAC(bool acStatus){
    controls->toggleAC(acStatus);
}

bool Train::getAC(){
    return controls->acOn;
}

void Train::setHeater(bool heaterStatus){
    controls->toggleHeater(heaterStatus);
}

bool Train::getHeater(){
    return controls->heaterOn;
}

void Train::setAdvertisements(bool adStatus){
    controls->toggleAdvertisments(adStatus);
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

