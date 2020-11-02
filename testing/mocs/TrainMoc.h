#ifndef TRAINMOC_H
#define TRAINMOC_H

#include <chrono>
#include <cstdint>
#include <string>
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
    bool doors;
    bool lights;
    bool headlights;
    int failureCode;
    bool ac;
    bool heater;
    bool ads;
    bool announcements;
    string message;
    uint8_t beaconData[64];
    uint64_t trackCircuit;

    TrainMoc(int newNumCars);
    uint64_t sendTrackCircuit();
    double getCurrentVelocity();
    void setPower(double newPower);             //Called by train controller to set power
    void setDoorStatus(bool);
    bool getDoorStatus();
    void setCabinLights(bool);
    bool getCabinLights();
    void setHeadlights(bool);
    bool getHeadlights();
    void setEmergencyBrake(bool);
    bool getEmergencyBrake();
    void setSystemFailure(int);
    int getSystemFailure();
    void setServiceBrake(bool);
    bool getServiceBrake();
    void setAC(bool);
    bool getAC();
    void setHeater(bool);
    bool getHeater();
    void setAdvertisements(bool);
    bool getAdvertisements();
    void setAnnouncements(bool, string);
    bool getAnnouncements();
    uint8_t* getBeaconData();
    string getAnnouncementMsg();

};

#endif // TRAINMOC_H
