#ifndef TRAINMOC_H
#define TRAINMOC_H

#include <chrono>
#include <cstdint>
#include <string>
#include "TrackModel/trackmodel_types.hpp"

using namespace TrackModel;
using namespace std;

class TrainMoc
{
public:
    int systemFailure;
    bool emergencyBrake;
    bool inYard = true;
    bool serviceBrake;
    int numCars;
    double power;
    bool leftDoors;
    bool rightDoors;
    bool lights;
    bool headlights;
    int failureCode;
    bool ac;
    bool heater;
    bool ads;
    bool announcements;
    int temp;
    double velocity;
    int count;
    string message;
    uint64_t trackCircuit;
    BeaconData beaconData;

    TrainMoc(int, string);
    uint64_t sendTrackCircuit();
    double getCurrentVelocity();
    void setPower(double newPower);             //Called by train controller to set power
    void setDoorStatus(bool);
    bool getDoorStatus();
    void setLeftDoorStatus(bool);
    bool getLeftDoorStatus();
    void setRightDoorStatus(bool);
    bool getRightDoorStatus();
    void setCabinLights(bool);
    bool getCabinLights();
    void setHeadlights(bool);
    bool getHeadlights();
    void setEmergencyBrake(bool);
    bool getEmergencyBrake();
    void setPassengerEBrake(bool);
    bool getPassengerEBrake();
    void setSystemFailure(int);
    int getSystemFailure();
    void setServiceBrake(bool);
    bool getServiceBrake();
    void setTemp(int);
    double getPower();
    double getTemp();
    void setAC(bool);
    bool getAC();
    void setHeater(bool);
    bool getHeater();
    void setAdvertisements(bool);
    bool getAdvertisements();
    void setAnnouncements(bool, string);
    bool getAnnouncements();
    TrackModel::BeaconData getBeaconData();
    string getAnnouncementMsg();
};

#endif // TRAINMOC_H
