#include <iostream>
#include "SerialPort.hpp"
#include "SerialPort.cpp"
#include <stdio.h>
#include <string.h>
#include "CabinControls.h"
#include "CabinControls.cpp"
#include "SpeedRegulator.h"
#include "SpeedRegulator.cpp"
#include "FailureDetector.h"
#include "FailureDetector.cpp"

using namespace std;

char portName[] = "\\\\.\\COM4";

#define MAX_DATA_LENGTH 255

char incomingData[MAX_DATA_LENGTH];

//Objects for communication with other classes
//SerialPort object
SerialPort serial_port(portName);

//CabinControls object
CabinControls cabin_controller;

//FailureDetector object
FailureDetector failure_detector;

//SpeedRegulator object
SpeedRegulator speed_regulator;

//Arduino SerialPort object
SerialPort *arduino;

//Blinking Delay
const unsigned int BLINKING_DELAY = 1000;

//If you want to send data then define "SEND" else comment it out
#define SEND

void receiveData(void)
{
    int readResult = arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
    string data(incomingData);

    if(data == "joystick up")
    {
        speed_regulator.incSetpointSpeed(.5);
    }
    else if(data == "joystick down")
    {
        speed_regulator.incSetpointSpeed(-.5);
    }
    else if(data.substr(0,4) == "KpKi")
    {
        speed_regulator.setKpAndKi(stod(data.substr(4,6)), stod(data.substr(10,6)));
    }
    else if(data == "cabinLightsOn")
    {
        cabin_controller.cabinLightsOn();
    }
    else if(data == "cabinAcOn")
    {  
        cabin_controller.cabinAcOn();
    }
    else if(data == "cabinHeatOn")
    {
        cabin_controller.cabinHeatOn();
    }
    else if(data == "cabinDoorsOpen")
    {
        cabin_controller.cabinDoorsOpen();
    }
    else if(data == "cabinAdvertisementsOn")
    {
        cabin_controller.cabinAdvertisementsOn();
    }
    else if(data == "cabinAnnouncementsOn")
    {
        cabin_controller.cabinAnnouncementsOn();
    }
    else if(data == "cabinLightsOff")
    {
        cabin_controller.cabinLightsOff();
    }
    else if(data == "cabinAcOff")
    {
        cabin_controller.cabinAcOff();
    }
    else if(data == "cabinHeatOff")
    {
        cabin_controller.cabinHeatOff();
    }
    else if(data == "cabinDoorsClosed")
    {
        cabin_controller.cabinDoorsClosed();
    }
    else if(data == "cabinAdvertisementsOff")
    {
        cabin_controller.cabinAdvertisementsOff();
    }
    else if(data == "cabinAnnouncementsOff")
    {
        cabin_controller.cabinAnnouncementsOff();
    }
    Sleep(1);
}

void writeData(unsigned int delayTime)
{
    //Create a system to encode all data to be returned to the interface in the string
    //char 1 = cabinLights
    //char 2 = cabinAc
    //char 3 = cabinHeat
    //char 4 = cabinDoorsClosed
    //char 5 = cabinAdvertisements
    //char 6 = cabinAnnouncements
    //char7-11 = authority
    //char12-16 = Kp
    //char17-21 = Ki
    //char22-26 = commandedSpeed
    //char27-31 = setpointSpeed
    //char32-36 = currentSpeed

    string outgoing_s = "";
    outgoing_s += cabin_controller.getCabinLights();
    outgoing_s += cabin_controller.getCabinAc();
    outgoing_s += cabin_controller.getCabinHeat();
    outgoing_s += cabin_controller.getCabinDoors();
    outgoing_s += cabin_controller.getCabinAdvertisements();
    outgoing_s += cabin_controller.getCabinAnnouncements();

    string power(speed_regulator.getPowerCmd(), 5);
    outgoing_s += power;

    string Kp(speed_regulator.getKp(), 5);
    outgoing_s += Kp;

    string Ki(speed_regulator.getKi(), 5);
    outgoing_s += Ki;

    string commandedSpeed(speed_regulator.getCommandedSpeed(), 5);
    outgoing_s += commandedSpeed;

    string setpointSpeed(speed_regulator.getSetpointSpeed(), 5);
    outgoing_s += setpointSpeed;

    string currentSpeed(speed_regulator.getCurrentSpeed(), 5);
    outgoing_s += currentSpeed;

    outgoing_s += "\n";

    char *outgoingData;
    strcpy(outgoingData, outgoing_s.c_str());

    arduino->writeSerialPort(outgoingData, MAX_DATA_LENGTH);
    Sleep(delayTime);
}

void autoConnect(void)
{
    //better than recusion
    //avoid stack overflows
    while(1) {
        // ui - searching
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

        #ifdef SEND
            while(arduino->isConnected()) writeData(BLINKING_DELAY);
        #else // SEND
            while(arduino->isConnected()) receiveData();
        #endif // SEND
    }
}

int main()
{
    arduino = new SerialPort(portName);

    autoConnect();  
}
