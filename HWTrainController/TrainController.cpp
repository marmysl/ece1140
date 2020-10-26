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
        cout << "Incoming Length: " << data.length() << endl;
        std::cout << "Incoming: " << data << std::endl;

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


        if(data.length() == 19)
        {

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

             if(data.substr(16,1) == "1") speedRegulator -> incSetpointSpeed(.5);

             if(data.substr(17,1) == "1") speedRegulator -> incSetpointSpeed(-.5);

             speedRegulator -> setKpAndKi(std::stod(data.substr(6,5)), std::stod(data.substr(11,5)));
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

    string outgoing_s = "";
    outgoing_s += to_string(trainModel -> getCabinLights());
    outgoing_s += to_string(trainModel -> getAC());
    outgoing_s += to_string(trainModel -> getHeater());
    outgoing_s += to_string(trainModel -> getDoorStatus());
    outgoing_s += to_string(trainModel -> getAdvertisements());
    outgoing_s += to_string(trainModel -> getAnnouncements());

    string authority(to_string(trainModel -> sendTrackCircuit()), 0, 5);
    outgoing_s += authority;
    std::cout << "Authority: " << authority << std::endl;

    while(outgoing_s.length() != 11) outgoing_s += " ";

    string Kp(to_string(speedRegulator -> getKp()), 0, 5);
    outgoing_s += Kp;
    std::cout << "Kp: " << Kp << std::endl;

    string Ki(to_string(speedRegulator -> getKi()), 0, 5);
    outgoing_s += Ki;
    std::cout << "Ki: " << Ki << std::endl;

    string commandedSpeed(to_string(trainModel -> sendTrackCircuit() << 32), 0, 5);
    outgoing_s += commandedSpeed;
    std::cout << "Commanded Speed: " << commandedSpeed << std::endl;

    while(outgoing_s.length() != 26) outgoing_s += " ";

    string setpointSpeed(to_string(speedRegulator -> getSetpointSpeed()), 0, 5);
    outgoing_s += setpointSpeed;
    std::cout << "Setpoint Speed: " << setpointSpeed << std::endl;

    string currentSpeed(to_string(trainModel -> getCurrentVelocity()), 0, 5);
    outgoing_s += currentSpeed;
    std::cout << "Current Velocity: " << currentSpeed << std::endl;


    outgoing_s += "\n";

   std::cout << "Outgoing: " << outgoing_s << std::endl;
    strcpy(outgoingData, outgoing_s.c_str());

    trainControllerPort.writeString(outgoing_s);
}
