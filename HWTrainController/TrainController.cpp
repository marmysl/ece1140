#include "TrainController.h"
#include "SerialPort.hpp"
#include "system_main.h"
#include "../CTCOffice/ctcoffice/CTCMode.h"

#include <QThread>
#include <string>
#include <QTimer>

TrainController::TrainController(CTCMode *m)
{
  //Create objects and assign them to pointers

    trainModel = new Train(5);
    mode = m;
    speedRegulator = new SpeedRegulator(trainModel, mode -> getMode());
    beacon = new BeaconDecoder();

    writeTimer = new QTimer();
    writeTimer->setInterval(ARDUINO_WAIT_TIME);

    // connect data receive method
    // trainControllerPort.dataReceived -> this.receiveData
    connect(&trainControllerPort, &SerialConn::dataReceived, this, &TrainController::recieveData);
    connect(writeTimer, &QTimer::timeout, this, &TrainController::writeData);

    writeTimer->start();
}

TrainController::~TrainController()
{
    forgetTrain(id);

    trainModel = nullptr;
    speedRegulator = nullptr;
    beacon = nullptr;
    delete writeTimer;
    delete trainModel;
    delete speedRegulator;
    delete beacon;
}

void TrainController::recieveData( char *buf, qint64 len )
{
    memcpy(incomingData, buf, len);
    incomingData[len] = '\0';

    if( len >= 0 )
    {
        string data(incomingData);
        //cout << "Incoming Length: " << data.length() << endl;
        std::cout << "Incoming: " << data.length() << std::endl;

          //Create a system to encode all data to be read from
          //char 0 = cabinLights
          //char 1 = cabinAc
          //char 2 = cabinHeat
          //char 3 = cabinDoorsClosedLeft
          //char 4 = cabinAdvertisements
          //char 5 = cabinAnnouncements
          //char6-10 = Kp
          //char11-15 = Ki
          //char16 = joystick up
          //char17 = joystick down
          //char18 = service brake
          //char19 = emergency brake
          //char20 = resolve failure button
          //char21 = headlights
          //char22 = release brake
          //char23 = cabinDoorsClosedRight


        if(data.length() == 26)
        {
             //Cabin Lights
             if(data.substr(0,1) == "1") trainModel -> setCabinLights(1);
             else trainModel -> setCabinLights(0);

             //Cabin AC
             if(data.substr(1,1) == "1") trainModel -> setAC(1);
             else trainModel -> setAC(0);

             //Cabin Heater
             if(data.substr(2,1) == "1") trainModel -> setHeater(1);
             else trainModel -> setHeater(0);

             //Door Status - Left
             if(data.substr(3,1) == "1") trainModel -> setDoorStatus(1);
             else trainModel -> setDoorStatus(0);

             //Door Status - Right
             if(data.substr(23,1) == "1") trainModel -> setDoorStatus(1);
             else trainModel -> setDoorStatus(0);

             //Advertisement Status
             if(data.substr(4,1) == "1") trainModel -> setAdvertisements(1);
             else trainModel -> setAdvertisements(0);

             //Announcement Status
             if(data.substr(5,1) == "1") trainModel -> setAnnouncements(1, beacon -> getAnnouncement());
             else trainModel -> setAnnouncements(0,beacon->getAnnouncement());

             //Increase Setpoint Speed
             if(data.substr(16,1) == "1") speedRegulator -> incSetpointSpeed(5);

             //Decrease Setpoint Speed
             if(data.substr(17,1) == "1") speedRegulator -> incSetpointSpeed(-5);

             //Adjust Kp and Ki
             speedRegulator -> setKpAndKi(std::stof(data.substr(6,5)), std::stof(data.substr(11,5)));

             //Pull Breaks
             if(data.substr(18,1) == "1") speedRegulator -> pullServiceBrake();
             if(data.substr(19,1) == "1") speedRegulator -> pullEmergencyBrake();

             //Resolve failure
             if(data.substr(20,1) == "1") trainModel -> setSystemFailure(0);

             //Headlights
             if(data.substr(21,1) == "1") trainModel -> setHeadlights(1);
             else trainModel -> setHeadlights(0);

             //Release brakes
             if(data.substr(22,1) == "1")
             {
                 trainModel -> setServiceBrake(0);
                 trainModel -> setEmergencyBrake(0);
             }
           }

        //Update the mode of operation
        speedRegulator -> setMode(mode -> getMode());

    }
}

void TrainController::writeData()
{
    //Create a system to encode all data to be returned to the interface in the string
    //char 0 = cabinLights
    //char 1 = cabinAc
    //char 2 = cabinHeat
    //char 3 = cabinDoorsClosedLeft
    //char 4 = cabinAdvertisements
    //char 5 = cabinAnnouncements
    //char6-10 = authority
    //char11-15 = Kp
    //char16-20 = Ki
    //char21-25 = commandedSpeed
    //char26-30 = setpointSpeed
    //char31-35 = currentSpeed
    //char36 = service brake
    //char37 = emergency brake
    //char 38-43 = power command
    //char 44 = failure code
    //char 45 = headlights
    //char 46 = mode
    //char 47 = cabinDoorsClosedRight
    //char 48 = newline

    //Create a string to add outgoing data to
    string outgoing_s = "";
    outgoing_s += to_string(trainModel -> getCabinLights());
    outgoing_s += to_string(trainModel -> getAC());
    outgoing_s += to_string(trainModel -> getHeater());
    outgoing_s += to_string(trainModel -> getDoorStatus());
    outgoing_s += to_string(trainModel -> getAdvertisements());
    outgoing_s += to_string(trainModel -> getAnnouncements());

    //Retrieve authority over the track circuit
    string authority(to_string(trainModel -> sendTrackCircuit() & 0xffffffff), 0, 5);
    outgoing_s += authority;

    //Fill in any missing characters with spaces
    while(outgoing_s.length() <= 10) outgoing_s += " ";

    //Get Ki value
    string Kp(to_string(speedRegulator -> getKp()), 0, 5);
    outgoing_s += Kp;

    //Fill in any missing characters with spaces
    while(outgoing_s.length() <= 15) outgoing_s += " ";

    //Get Kp value
    string Ki(to_string(speedRegulator -> getKi()), 0, 5);
    outgoing_s += Ki;

    //Fill in any missing characters with spaces
    while(outgoing_s.length() <= 20) outgoing_s += " ";

    //Retrieve commanded speed
    string commandedSpeed(to_string(trainModel -> sendTrackCircuit() >> 32), 0, 5);
    outgoing_s += commandedSpeed;

    //Fill in any missing characters with spaces
    while(outgoing_s.length() <= 25) outgoing_s += " ";

    //Retrieve setpoint speed
    string setpointSpeed(to_string(speedRegulator -> getSetpointSpeed()), 0, 5);
    outgoing_s += setpointSpeed;

    //Fill in any missing characters with spaces
    while(outgoing_s.length() <= 30) outgoing_s += " ";

    //Retrieve current speed
    string currentSpeed(to_string(trainModel -> getCurrentVelocity()), 0, 5);
    outgoing_s += currentSpeed;

    //Fill in any missing characters with spaces
    while(outgoing_s.length() <= 35) outgoing_s += " ";

    //Retrieve trainMdel data
    outgoing_s+= to_string(trainModel -> getServiceBrake());
    std::cout << "Service Brake: " << trainModel -> getServiceBrake() << std::endl;
    outgoing_s+= to_string(trainModel -> getEmergencyBrake());
    std::cout << "Emergency Brake: " << trainModel -> getEmergencyBrake() << std::endl;

    string power(to_string(speedRegulator -> getPowerCmd()), 0, 6);
    outgoing_s += power;

    //Fill in any missing characters with spaces
    while(outgoing_s.length() <= 43) outgoing_s += " ";

    outgoing_s += to_string(trainModel -> getSystemFailure());

    outgoing_s += to_string(trainModel -> getHeadlights());

    outgoing_s += to_string(mode -> getMode());

    outgoing_s += to_string(trainModel -> getDoorStatus());

    outgoing_s += "\n";

    std::cout << "Outgoing: " << outgoing_s << std::endl;
    strcpy(outgoingData, outgoing_s.c_str());

    trainControllerPort.writeString(outgoing_s);
}

