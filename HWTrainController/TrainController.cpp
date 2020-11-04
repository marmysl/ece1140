#include "TrainController.h"
#include "SerialPort.hpp"
#include "system_main.h"

#include <QThread>
#include <string>
#include <QTimer>

TrainController::TrainController()
{
    //Create objects and assign them to pointers

    trainModel = new Train(5);
    speedRegulator = new SpeedRegulator(trainModel);
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
          //char 3 = cabinDoorsClosed
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


        if(data.length() == 25)
        {
             std::cout << "Incoming: " << data << std::endl;
             if(data.substr(0,1) == "1") trainModel -> setCabinLights(1);
             else trainModel -> setCabinLights(0);

             if(data.substr(1,1) == "1") trainModel -> setAC(1);
             else trainModel -> setAC(0);

             if(data.substr(2,1) == "1") trainModel -> setHeater(1);
             else trainModel -> setHeater(0);

             if(data.substr(3,1) == "1") trainModel -> setDoorStatus(1);
             else trainModel -> setDoorStatus(0);

             if(data.substr(4,1) == "1") trainModel -> setAdvertisements(1);
             else trainModel -> setAdvertisements(0);

             if(data.substr(5,1) == "1") trainModel -> setAnnouncements(1, beacon -> getAnnouncement());
             else trainModel -> setAnnouncements(0,beacon->getAnnouncement());

             if(data.substr(16,1) == "1") speedRegulator -> incSetpointSpeed(5);

             if(data.substr(17,1) == "1") speedRegulator -> incSetpointSpeed(-5);

             speedRegulator -> setKpAndKi(std::stod(data.substr(6,5)), std::stod(data.substr(11,5)));

             if(data.substr(18,1) == "1") speedRegulator -> pullServiceBrake();
             if(data.substr(19,1) == "1") speedRegulator -> pullEmergencyBrake();
             if(data.substr(20,1) == "1") trainModel -> setSystemFailure(0);
             if(data.substr(21,1) == "1") trainModel -> setHeadlights(1);
             else trainModel -> setHeadlights(0);

             if(data.substr(22,1) == "1")
             {
                 trainModel -> setServiceBrake(0);
                 trainModel -> setEmergencyBrake(0);
             }
           }

    }
}

void TrainController::writeData()
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
    //char36 = service brake
    //char37 = emergency brake
    //char 38-43 = power command
    //char 44 = failure code
    //char 45 = headlights

    string outgoing_s = "";
    outgoing_s += to_string(trainModel -> getCabinLights());
    outgoing_s += to_string(trainModel -> getAC());
    outgoing_s += to_string(trainModel -> getHeater());
    outgoing_s += to_string(trainModel -> getDoorStatus());
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
    std::cout << "Service Brake: " << trainModel -> getServiceBrake() << std::endl;
    outgoing_s+= to_string(trainModel -> getEmergencyBrake());
    std::cout << "Emergency Brake: " << trainModel -> getEmergencyBrake() << std::endl;

    string power(to_string(speedRegulator -> getPowerCmd()), 0, 6);
    outgoing_s += power;
    while(outgoing_s.length() <= 43) outgoing_s += " ";

    outgoing_s += to_string(trainModel -> getSystemFailure());

    outgoing_s += to_string(trainModel -> getHeadlights());

    outgoing_s += "\n";

    std::cout << "Outgoing: " << outgoing_s << std::endl;
    strcpy(outgoingData, outgoing_s.c_str());

    trainControllerPort.writeString(outgoing_s);
}

