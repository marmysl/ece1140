#include "TrainController.h"
#include "SerialPort.hpp"

#include <QThread>

TrainController::TrainController()
{
    //Create objects and assign them to pointers

	train_model = new Train(5);
	cout << "here" << endl;
	speed_regulator = new SpeedRegulator(train_model);
	speed_regulator -> decodeTrackSignal();
	cabin_controller = new CabinControls();

//	//Connects the arduino to the serial port
//	std::cout << "Searching in progress";
     
//     // wait connection
//	std::cout << "Searching in progress";
//    while (!arduino->isOpen()) {
//        std::cout << ".";
//        arduino->open(QIODevice::ReadWrite);
//        QThread::msleep(500);
//    }

//    //Checking if arduino is connected or not
//    if (arduino->isOpen()) {
//        std::cout  << std::endl << "Connection established at port " << portName << std::endl;
//    }
}

TrainController::~TrainController()
{
	arduino = nullptr;
	train_model = nullptr;
	speed_regulator = nullptr;
	cabin_controller = nullptr;
	delete arduino;
	delete train_model;
	delete speed_regulator;
	delete cabin_controller;
}

void TrainController::recieveData()
{
    int readResult = trainControllerPort.read(incomingData, ARDUINO_BUF_LENGTH);

    if( readResult > 0 )
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


        std::cout << "Incoming: " << data << std::endl;

        if(!data.empty())
        {
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
        }
    }

    QThread::msleep(900);
}

void TrainController::writeData(int delayTime)
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

    trainControllerPort.read(outgoingData, ARDUINO_BUF_LENGTH);

    QThread::msleep(delayTime);
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
    while(hwTrainControllerConnected)
	{
		recieveData();
		writeData(900);
		speed_regulator -> calculatePowerCmd();
		cout << "Power: " << speed_regulator -> getPowerCmd() << endl;
		cout << "Incoming: " << getInput() << endl;
		cout << "Outgoing: " << getOutput() << endl;
	}
}
