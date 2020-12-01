#include "TrainModelControls.h"


TrainModelControls::TrainModelControls(){

}

void TrainModelControls::toggleDoor(bool doorStatus){
    doorOpen = doorStatus;
}

void TrainModelControls::toggleLeftDoor(bool doorStatus){
    doorLeftOpen = doorStatus;
}

void TrainModelControls::toggleRightDoor(bool doorStatus){
    doorRightOpen = doorStatus;
}

void TrainModelControls::toggleCabinLights(bool cabLightStatus){
    cabinLights = cabLightStatus;
}

void TrainModelControls::toggleHeadlights(bool headlightStatus){
    headlightsOn = headlightStatus;
}

void TrainModelControls::toggleAdvertisments(bool adStatus){
    advertisementsOn = adStatus;
}

void TrainModelControls::toggleAnnouncements(bool annStatus){
    announcementsOn = annStatus;
}

void TrainModelControls::setAnn(string annSet){
    announcements = annSet;
}

string TrainModelControls::getAnn(){
    return announcements;
}

void TrainModelControls::toggleAC(bool acStatus){
    acOn = acStatus;
}

void TrainModelControls::toggleHeater(bool heaterStatus){
    heaterOn = heaterStatus;
}
