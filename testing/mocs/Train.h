#ifndef TRAIN_H
#define TRAIN_H

#include <chrono>
#include <cstdint>
#include <string>
using namespace std;

class Train
{
public:
    int systemFailure;
    bool emergencyBrake;
    bool inYard = true;
    bool serviceBrake;
    int numCars;
    double power;
    bool doorsLeft;
    bool doorsRight;
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

    Train(int newNumCars);
    uint64_t sendTrackCircuit();
    double getCurrentVelocity();
    void setPower(double newPower);             //Called by train controller to set power
    void setDoorStatusLeft(bool);
    bool getDoorStatusLeft();
    void setDoorStatusRight(bool);
    bool getDoorStatusRight();
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

#endif // TRAIN_H
