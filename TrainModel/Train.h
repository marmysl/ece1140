
#ifndef TRAIN_H
#define TRAIN_H
#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
#include "TrainModelUI.h"
#include "TrainModelControls.h"
#include "../TrackModel/trackmodel_types.hpp"

#include <chrono>
#include <cstdint>
using namespace std;

class Train
{
public:
    TrainModelUI *w;
    TrainModelControls *controls;
    TrainModelMath *math;
    TrainModelUpdateBlock *block;
    int systemFailure = 0;

    Train(int newNumCars, string lineType);
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
    double getSafeStoppingDistance();
    void updateUI();
};

#endif // TRAIN_H
