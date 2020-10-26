#include "TrainController.h"
#include "SerialPort.hpp"
#include "system_main.h"

#include <QThread>
#include <string>
#include <QTimer>

TrainController::TrainController()
{
    //Create objects and assign them to pointers

    train = new Train(5);
	cout << "here" << endl;
    speed_regulator = new SpeedRegulator(train);
	speed_regulator -> decodeTrackSignal();
	cabin_controller = new CabinControls();

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

    train = nullptr;
	speed_regulator = nullptr;
    cabin_controller = nullptr;
    delete writeTimer;
    delete train;
	delete speed_regulator;
	delete cabin_controller;
}

void TrainController::recieveData( char *buf, qint64 len )
{
    memcpy(incomingData, buf, len);
    incomingData[len] = '\0';

    if( len >= 0 )
    {
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


        if(!data.empty())
        {
            std::cout << "Incoming: " << data.substr(0, 17) << std::endl;

            if(data.substr(0,1) == "1") cabin_controller -> cabinLightsOn();
            else cabin_controller -> cabinLightsOff();

            if(data.substr(1,1) == "1") cabin_controller -> cabinAcOn();
            else cabin_controller -> cabinAcOff();

            if(data.substr(2,1) == "1") cabin_controller -> cabinHeatOn();
            else cabin_controller -> cabinHeatOff();

            if(data.substr(3,1) == "1") cabin_controller -> cabinDoorsOpen();
            else cabin_controller -> cabinDoorsClosed();

            if(data.substr(4,1) == "1") cabin_controller -> cabinAdvertisementsOn();
            else cabin_controller -> cabinAdvertisementsOff();

            if(data.substr(5,1) == "1") cabin_controller -> cabinAnnouncementsOn();
            else cabin_controller -> cabinAnnouncementsOff();

            if(data.substr(16,1) == "1") speed_regulator -> incSetpointSpeed(.5);

            if(data.substr(17,1) == "1") speed_regulator -> incSetpointSpeed(-.5);

            speed_regulator -> setKpAndKi(std::stod(data.substr(6,5)), std::stod(data.substr(11,5)));

            speed_regulator -> calculatePowerCmd();
            cout << "Power: " << speed_regulator -> getPowerCmd() << endl;
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
    outgoing_s += to_string(cabin_controller -> getCabinLights());
    outgoing_s += to_string(cabin_controller -> getCabinAc());
    outgoing_s += to_string(cabin_controller -> getCabinHeat());
    outgoing_s += to_string(cabin_controller -> getCabinDoors());
    outgoing_s += to_string(cabin_controller -> getCabinAdvertisements());
    outgoing_s += to_string(cabin_controller -> getCabinAnnouncements());

    string authority(to_string(speed_regulator -> getAuthority()), 0, 5);
    outgoing_s += authority;

    string Kp(to_string(speed_regulator -> getKp()), 0, 5);
    outgoing_s += Kp;

    string Ki(to_string(speed_regulator -> getKi()), 0, 5);
    outgoing_s += Ki;

    string commandedSpeed(to_string(speed_regulator -> getCommandedSpeed()), 0, 5);
    outgoing_s += commandedSpeed;

    string setpointSpeed(to_string(speed_regulator -> getSetpointSpeed()), 0, 5);
    outgoing_s += setpointSpeed;

    string currentSpeed(to_string(speed_regulator -> getCurrentSpeed()), 0, 5);
    outgoing_s += currentSpeed;

    outgoing_s += "\n";

    std::cout << "Outgoing: " << outgoing_s << std::endl;
    strcpy(outgoingData, outgoing_s.c_str());

    trainControllerPort.writeString(outgoing_s);
}

string TrainController::getInput()
{
	string data(incomingData);
	return data;
}
string TrainController::getOutput()
{
	string data(outgoingData);
	return data;
}

void TrainController::dispatch()
{
//    while(trainControllerPort.isConnected())
//	{
//        //recieveData();
//		writeData(900);
//		speed_regulator -> calculatePowerCmd();
//		cout << "Power: " << speed_regulator -> getPowerCmd() << endl;
//		cout << "Incoming: " << getInput() << endl;
//		cout << "Outgoing: " << getOutput() << endl;
//	}
}
