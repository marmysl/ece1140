#include "TrainMoc.h"

using namespace std;

TrainMoc::TrainMoc(int newNumCars)
{
    numCars = newNumCars;
    doors = 0;
    lights = 0;
    headlights = 0;
    failureCode = 0;
    ac = 0;
    heater = 0;
    ads = 0;
    serviceBrake = 0;
    emergencyBrake = 0;
}

void TrainMoc::setPower(double newPower){             //Called by train controller to set power
    power = newPower;
}

uint64_t TrainMoc::sendTrackCircuit(){
    return trackCircuit;
}

double TrainMoc::getCurrentVelocity(){
    return power*2;
}

void TrainMoc::setDoorStatus(bool doorStatus){
    doors = doorStatus;
}

bool TrainMoc::getDoorStatus(){
    return doors;
}

void TrainMoc::setCabinLights(bool lightStatus){
    lights = lightStatus;
}

bool TrainMoc::getCabinLights(){
    return lights;
}

void TrainMoc::setHeadlights(bool headlightStatus){
    headlights = headlightStatus;
}

bool TrainMoc::getHeadlights(){
    return headlights;
}

void TrainMoc::setEmergencyBrake(bool eBrakeStatus){
    emergencyBrake = eBrakeStatus;
}

bool TrainMoc::getEmergencyBrake(){
    return emergencyBrake;
}

void TrainMoc::setSystemFailure(int failStat){
    failureCode = failStat;
}

int TrainMoc::getSystemFailure(){
    return failureCode;
}

void TrainMoc::setServiceBrake(bool servBrake){
    serviceBrake = servBrake;
}

bool TrainMoc::getServiceBrake(){
    return serviceBrake;
}

void TrainMoc::setAC(bool acStatus){
    ac = acStatus;
}

bool TrainMoc::getAC(){
    return ac;
}

void TrainMoc::setHeater(bool heaterStatus){
    heater = heaterStatus;
}

bool TrainMoc::getHeater(){
    return heater;
}

void TrainMoc::setAdvertisements(bool adStatus){
    ads = adStatus;
}

bool TrainMoc::getAdvertisements(){
    return ads;
}

void TrainMoc::setAnnouncements(bool annStatus, string annString){
    announcements = annStatus;
    message = annString;
}

bool TrainMoc::getAnnouncements(){
    return announcements;
}

uint8_t* TrainMoc::getBeaconData(){
    return beaconData;
}

string TrainMoc::getAnnouncementMsg(){
    return message;
}

