#include "TrainControllerMoc.h"

TrainControllerMoc::TrainControllerMoc(bool m)
{
    //Create objects and assign them to pointers

      trainModel = new Train(5);
      mode = m;
      speedRegulator = new SpeedRegulator(trainModel, m);
      beacon = new BeaconDecoder();
}
void TrainControllerMoc::receiveData(string simData)
{
    if(simData.substr(0,1) == "1") trainModel -> setCabinLights(1);
    else trainModel -> setCabinLights(0);
    if(simData.substr(1,1) == "1") trainModel -> setAC(1);
    else trainModel -> setAC(0);
    if(simData.substr(2,1) == "1") trainModel -> setHeater(1);
    else trainModel -> setHeater(0);
    if(simData.substr(3,1) == "1") trainModel -> setDoorStatusLeft(1);
    else trainModel -> setDoorStatusLeft(0);
    if(simData.substr(23,1) == "1") trainModel -> setDoorStatusRight(1);
    else trainModel -> setDoorStatusRight(0);
    if(simData.substr(4,1) == "1") trainModel -> setAdvertisements(1);
    else trainModel -> setAdvertisements(0);
    if(simData.substr(5,1) == "1") trainModel -> setAnnouncements(1, beacon -> getAnnouncement());
    else trainModel -> setAnnouncements(0,beacon->getAnnouncement());
    if(simData.substr(16,1) == "1") speedRegulator -> incSetpointSpeed(5);
    if(simData.substr(17,1) == "1") speedRegulator -> incSetpointSpeed(-5);
    speedRegulator -> setKpAndKi(std::stod(simData.substr(6,5)), std::stod(simData.substr(11,5)));
    if(simData.substr(18,1) == "1") speedRegulator -> pullServiceBrake();
    if(simData.substr(19,1) == "1") speedRegulator -> pullEmergencyBrake();
    if(simData.substr(20,1) == "1") trainModel -> setSystemFailure(0);
    if(simData.substr(21,1) == "1") trainModel -> setHeadlights(1);
    else trainModel -> setHeadlights(0);
    if(simData.substr(22,1) == "1")
    {
        trainModel -> setServiceBrake(0);
        trainModel -> setEmergencyBrake(0);
    }
}
std::string TrainControllerMoc::writeData()
{
    string outgoing_s = "";
    outgoing_s += to_string(trainModel -> getCabinLights());
    outgoing_s += to_string(trainModel -> getAC());
    outgoing_s += to_string(trainModel -> getHeater());
    outgoing_s += to_string(trainModel -> getDoorStatusLeft());
    outgoing_s += to_string(trainModel -> getAdvertisements());
    outgoing_s += to_string(trainModel -> getAnnouncements());
    string authority(to_string(trainModel -> sendTrackCircuit() & 0xffffffff), 0, 5);
    outgoing_s += authority;
    while(outgoing_s.length() <= 10) outgoing_s += " ";
    string Kp(to_string(speedRegulator -> getKp()), 0, 5);
    outgoing_s += Kp;
    while(outgoing_s.length() <= 15) outgoing_s += " ";
    string Ki(to_string(speedRegulator -> getKi()), 0, 5);
    outgoing_s += Ki;
    while(outgoing_s.length() <= 20) outgoing_s += " ";
    string commandedSpeed(to_string(trainModel -> sendTrackCircuit() >> 32), 0, 5);
    outgoing_s += commandedSpeed;
    while(outgoing_s.length() <= 25) outgoing_s += " ";
    string setpointSpeed(to_string(speedRegulator -> getSetpointSpeed()), 0, 5);
    outgoing_s += setpointSpeed;
    while(outgoing_s.length() <= 30) outgoing_s += " ";
    string currentSpeed(to_string(trainModel -> getCurrentVelocity()), 0, 5);
    outgoing_s += currentSpeed;
    while(outgoing_s.length() <= 35) outgoing_s += " ";
    outgoing_s+= to_string(trainModel -> getServiceBrake());
    outgoing_s+= to_string(trainModel -> getEmergencyBrake());
    string power(to_string(speedRegulator -> getPowerCmd()), 0, 6);
    outgoing_s += power;
    while(outgoing_s.length() <= 43) outgoing_s += " ";
    outgoing_s += to_string(trainModel -> getSystemFailure());
    outgoing_s += to_string(trainModel -> getHeadlights());
    outgoing_s += to_string(mode);
    outgoing_s += to_string(trainModel -> getDoorStatusRight());
    return outgoing_s;
}
BeaconDecoder* TrainControllerMoc::getBeacon()
{
    return beacon;
}
SpeedRegulator* TrainControllerMoc::getSpeedRegulator()
{
    return speedRegulator;
}
Train* TrainControllerMoc::getTrainModel()
{
    return trainModel;
}
void TrainControllerMoc::setMode(bool m)
{
    mode = m;
}
bool TrainControllerMoc::getMode()
{
    return mode;
}
