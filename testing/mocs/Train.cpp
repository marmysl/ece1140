#include "Train.h"

using namespace std;

Train::Train(int newNumCars)
{
    numCars = newNumCars;
    doorsLeft = 0;
    doorsRight = 0;
    lights = 0;
    headlights = 0;
    failureCode = 0;
    ac = 0;
    heater = 0;
    ads = 0;
    serviceBrake = 0;
    emergencyBrake = 0;
}

void Train::setPower(double newPower){             //Called by train controller to set power
    power = newPower;
}

uint64_t Train::sendTrackCircuit(){
    return trackCircuit;
}

double Train::getCurrentVelocity(){
    return power*2;
}

void Train::setDoorStatusLeft(bool doorStatus){
    doorsLeft = doorStatus;
}

void Train::setDoorStatusRight(bool doorStatus){
    doorsRight = doorStatus;
}

bool Train::getDoorStatusLeft(){
    return doorsLeft;
}

bool Train::getDoorStatusRight(){
    return doorsRight;
}

void Train::setCabinLights(bool lightStatus){
    lights = lightStatus;
}

bool Train::getCabinLights(){
    return lights;
}

void Train::setHeadlights(bool headlightStatus){
    headlights = headlightStatus;
}

bool Train::getHeadlights(){
    return headlights;
}

void Train::setEmergencyBrake(bool eBrakeStatus){
    emergencyBrake = eBrakeStatus;
}

bool Train::getEmergencyBrake(){
    return emergencyBrake;
}

void Train::setSystemFailure(int failStat){
    failureCode = failStat;
}

int Train::getSystemFailure(){
    return failureCode;
}

void Train::setServiceBrake(bool servBrake){
    serviceBrake = servBrake;
}

bool Train::getServiceBrake(){
    return serviceBrake;
}

void Train::setAC(bool acStatus){
    ac = acStatus;
}

bool Train::getAC(){
    return ac;
}

void Train::setHeater(bool heaterStatus){
    heater = heaterStatus;
}

bool Train::getHeater(){
    return heater;
}

void Train::setAdvertisements(bool adStatus){
    ads = adStatus;
}

bool Train::getAdvertisements(){
    return ads;
}

void Train::setAnnouncements(bool annStatus, string annString){
    announcements = annStatus;
    message = annString;
}

bool Train::getAnnouncements(){
    return announcements;
}

uint8_t* Train::getBeaconData(){
    return beaconData;
}

string Train::getAnnouncementMsg(){
    return message;
}

