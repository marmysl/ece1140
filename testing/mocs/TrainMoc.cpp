#include "TrainMoc.h"
#include "../../TrackModel/trackmodel_types.hpp"
using namespace TrackModel;

TrainMoc::TrainMoc(int newNumCars, string lineType)
{
    numCars = newNumCars;
    leftDoors = 0;
    rightDoors = 0;
    lights = 0;
    headlights = 0;
    failureCode = 0;
    ac = 0;
    heater = 0;
    ads = 0;
    serviceBrake = 0;
    emergencyBrake = 0;
    power = 0;
    temp = 0;
    velocity = 0;
    count = 0;
    message = "";
}


uint64_t TrainMoc::sendTrackCircuit()
{
    if(failureCode == 3)
    {
        return 0xFFFFFFFFFFFFFFFF;
    }
    return trackCircuit;
}
double TrainMoc::getCurrentVelocity()
{
    return 5;
}
void TrainMoc::setPower(double newPower)
{
    if(failureCode == 2) power = 0;
    else power = newPower;
}
void TrainMoc::setLeftDoorStatus(bool door)
{
    leftDoors = door;
}
bool TrainMoc::getLeftDoorStatus()
{
    return leftDoors;
}
void TrainMoc::setRightDoorStatus(bool door)
{
    rightDoors = door;
}
bool TrainMoc::getRightDoorStatus()
{
    return rightDoors;
}
void TrainMoc::setCabinLights(bool l)
{
    lights = l;
}
bool TrainMoc::getCabinLights()
{
    return lights;
}
void TrainMoc::setHeadlights(bool h)
{
    headlights = h;
}
bool TrainMoc::getHeadlights()
{
    return headlights;
}
void TrainMoc::setEmergencyBrake(bool b)
{
    emergencyBrake = b;
}
bool TrainMoc::getEmergencyBrake()
{
    return emergencyBrake;
}
void TrainMoc::setPassengerEBrake(bool b)
{
    emergencyBrake = b;
}
bool TrainMoc::getPassengerEBrake()
{
    return emergencyBrake;
}
void TrainMoc::setSystemFailure(int code)
{
    failureCode = code;
}
int TrainMoc::getSystemFailure()
{
    return failureCode;
}
void TrainMoc::setServiceBrake(bool b)
{
    serviceBrake = b;
}
bool TrainMoc::getServiceBrake()
{
    return serviceBrake;
}
void TrainMoc::setTemp(int t)
{
    temp = t;
}
double TrainMoc::getPower()
{
    return power;
}
double TrainMoc::getTemp()
{
    return temp;
}
void TrainMoc::setAC(bool a)
{
    ac = a;
}
bool TrainMoc::getAC()
{
    return ac;
}
void TrainMoc::setHeater(bool h)
{
    heater = h;
}
bool TrainMoc::getHeater()
{
    return heater;
}
void TrainMoc::setAdvertisements(bool a)
{
    ads = a;
}
bool TrainMoc::getAdvertisements()
{
    return ads;
}
void TrainMoc::setAnnouncements(bool a, string str)
{
    announcements = a;
    message = str;
}
bool TrainMoc::getAnnouncements()
{
    return announcements;
}
TrackModel::BeaconData TrainMoc::getBeaconData()
{
    return beaconData;
}
string TrainMoc::getAnnouncementMsg()
{
    return message;
}

