#include <iostream>
#include "SerialPort.hpp"
#include "SerialPort.cpp"
#include <stdio.h>
#include <string>
#include "CabinControls.h"
#include "CabinControls.cpp"
#include "SpeedRegulator.h"
#include "SpeedRegulator.cpp"
#include "FailureDetector.h"
#include "FailureDetector.cpp"
#include "../TrainModel/Train.h"

using namespace std;

char portName[] = "\\\\.\\COM4";

char incomingData[255];
char outgoingData[255];

//Arduino SerialPort object
SerialPort *arduino;

//TrainModel Object
Train train_model(5);

//CabinControls object
CabinControls cabin_controller;

//FailureDetector object
FailureDetector failure_detector;

//SpeedRegulator object
SpeedRegulator speed_regulator(&train_model);

//If you want to send data then define "SEND" else comment it out
#define SEND

void exampleReceiveData(void)
{
    int readResult = arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
    string data(incomingData);

      //Create a system to encode all data to be read from
      //char 0 = cabinLights
      //char 1 = cabinAc
      //char 2 = cabinHeat
      //char 3 = cabinDoorsClosed
      //char 4 = cabinAdvertisements
      //char 5 = cabinAnnouncements
      //char6-10 = Kp
      //char11-15 = Ki
      //char16 = joystick up
      //char17 = joystick down


    std::cout << "Incoming: " << data << std::endl;

    if(!data.empty())
    {
        if(data.substr(0,1) == "1") cabin_controller.cabinLightsOn();
        else cabin_controller.cabinLightsOff();

        if(data.substr(1,1) == "1") cabin_controller.cabinAcOn();
        else cabin_controller.cabinAcOff();

        if(data.substr(2,1) == "1") cabin_controller.cabinHeatOn();
        else cabin_controller.cabinHeatOff();

        if(data.substr(3,1) == "1") cabin_controller.cabinDoorsOpen();
        else cabin_controller.cabinDoorsClosed();

        if(data.substr(4,1) == "1") cabin_controller.cabinAdvertisementsOn();
        else cabin_controller.cabinAdvertisementsOff();

        if(data.substr(5,1) == "1") cabin_controller.cabinAnnouncementsOn();
        else cabin_controller.cabinAnnouncementsOff();

        if(data.substr(16,1) == "1") speed_regulator.incSetpointSpeed(.5);

        if(data.substr(17) == "1") speed_regulator.incSetpointSpeed(-.5);

        speed_regulator.setKpAndKi(std::stod(data.substr(6,5)), std::stod(data.substr(11,5)));
    }  
    Sleep(100);
}

void exampleWriteData(unsigned int delayTime)
{
    //Create a system to encode all data to be returned to the interface in the string
    //char 0 = cabinLights
    //char 1 = cabinAc
    //char 2 = cabinHeat
    //char 3 = cabinDoorsClosed
    //char 4 = cabinAdvertisements
    //char 5 = cabinAnnouncements
    //char6-10 = authority
    //char11-15 = Kp
    //char16-20 = Ki
    //char21-25 = commandedSpeed
    //char26-30 = setpointSpeed
    //char31-35 = currentSpeed

    string outgoing_s = "";
    outgoing_s += to_string(cabin_controller.getCabinLights());
    outgoing_s += to_string(cabin_controller.getCabinAc());
    outgoing_s += to_string(cabin_controller.getCabinHeat());
    outgoing_s += to_string(cabin_controller.getCabinDoors());
    outgoing_s += to_string(cabin_controller.getCabinAdvertisements());
    outgoing_s += to_string(cabin_controller.getCabinAnnouncements());

    string power(to_string(speed_regulator.getAuthority()), 0, 5);
    outgoing_s += power;

    string Kp(to_string(speed_regulator.getKp()), 0, 5);
    outgoing_s += Kp;

    string Ki(to_string(speed_regulator.getKi()), 0, 5);
    outgoing_s += Ki;

    string commandedSpeed(to_string(speed_regulator.getCommandedSpeed()), 0, 5);
    outgoing_s += commandedSpeed;

    string setpointSpeed(to_string(speed_regulator.getSetpointSpeed()), 0, 5);
    outgoing_s += setpointSpeed;

    string currentSpeed(to_string(speed_regulator.getCurrentSpeed()), 0, 5);
    outgoing_s += currentSpeed;

    outgoing_s += "\n";

    std::cout << "Outgoing: " << outgoing_s << std::endl;
    strcpy(outgoingData, outgoing_s.c_str());

    arduino->writeSerialPort(outgoingData, MAX_DATA_LENGTH);
    Sleep(delayTime);
}

void autoConnect(void)
{
        std::cout << "Searching in progress";
        // wait connection
        while (!arduino->isConnected()) {
            Sleep(100);
            std::cout << ".";
            arduino = new SerialPort(portName);
        }

        //Checking if arduino is connected or not
        if (arduino->isConnected()) {
            std::cout  << std::endl << "Connection established at port " << portName << std::endl;
        }
}

int main()
{
    arduino = new SerialPort(portName);

    autoConnect();
    while(arduino -> isConnected())
    {
        exampleReceiveData();
        std::cout << "Cabin Lights: " << cabin_controller.getCabinLights() << std::endl;
        exampleWriteData(100);
    }
}
