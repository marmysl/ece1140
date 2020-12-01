#include "TrainController.h"
#include "SerialPort.hpp"
#include "system_main.h"
#include "../CTCOffice/ctcoffice/CTCMode.h"
#include "../TrackModel/trackmodel_types.hpp"

#include <QThread>
#include <string>
#include <QTimer>

TrainController::TrainController(CTCMode *m, int numCars, std::string lineType)
{
    //Create objects and assign them to pointers
    trainModel = new Train(numCars, lineType);
    mode = m;
    beacon = new BeaconDecoder();
    speedRegulator = new SpeedRegulator(trainModel, mode, beacon);

    //Set up the timer to write data to the Arduino
    writeTimer = new QTimer();
    writeTimer->setInterval(ARDUINO_WAIT_TIME);

    //Connect data receive method
    connect(&trainControllerPort, &SerialConn::dataReceived, this, &TrainController::recieveData);
    connect(writeTimer, &QTimer::timeout, this, &TrainController::writeData);

    //Start the writing data timer
    writeTimer->start();

    //Pull the service brake when the train is created
    speedRegulator -> pullServiceBrake();

    //Initialize the stopTimerStarted flag to be 0
    stopTimerStarted = 0;

    //Initialize the stopAlreadyOccurred flag to be 0
    stopAlreadyOccurred = 0;

    //Initialize start to be the current time
    //start = systemClock -> currentTime();
}

TrainController::~TrainController()
{
    forgetTrain(id);

    trainModel = nullptr;
    speedRegulator = nullptr;
    beacon = nullptr;
    writeTimer = nullptr;
    delete writeTimer;
    delete trainModel;
    delete speedRegulator;
    delete beacon;
}

void TrainController::recieveData( char *buf, qint64 len )
{
    //Recieve the data from the serial port in the correct format
    memcpy(incomingData, buf, len);

    //Add the null terminator to the data being received
    incomingData[len] = '\0';

    //If the length is above 0, then start reading the data
    if( len >= 0 )
    {
        //Convert the incoming data to a string
        string data(incomingData);
        cout << "Incoming Length: " << data.length() << endl;

          //Create a system to encode all data to be read from
          //char 0 = cabinLights
          //char 1 = cabinAc
          //char 2 = cabinHeat
          //char 3 = cabinDoorsLeftClosed
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
          //char 23 = cabinDoorsRightCloded

        //Only update the data if the correct amount of data is received
        if(data.length() == 26)
        {
             //Updates the cabin lights
             if(data.substr(0,1) == "1") trainModel -> setCabinLights(1);
             else trainModel -> setCabinLights(0);

             //Updates the air conditioning
             if(data.substr(1,1) == "1") trainModel -> setAC(1);
             else trainModel -> setAC(0);

             //Updates the heater
             if(data.substr(2,1) == "1") trainModel -> setHeater(1);
             else trainModel -> setHeater(0);

             //Updates the left doors
             if(data.substr(3,1) == "1" || (!stopAlreadyOccurred && stopTimerStarted && trainModel -> getLeftDoorStatus())) trainModel -> setLeftDoorStatus(1);
             else trainModel -> setLeftDoorStatus(0);

             //Updates the advertisements
             if(data.substr(4,1) == "1") trainModel -> setAdvertisements(1);
             else trainModel -> setAdvertisements(0);

             //Updates the announcements
             if(data.substr(5,1) == "1") trainModel -> setAnnouncements(1, beacon -> getAnnouncement());
             else trainModel -> setAnnouncements(0,beacon->getAnnouncement());

             //Increments the setpoint speed if the joystick indicates
             if(data.substr(16,1) == "1") speedRegulator -> incSetpointSpeed(5);

             //Decrements the setpoint speed if the joystick indicates
             if(data.substr(17,1) == "1") speedRegulator -> incSetpointSpeed(-5);

             //Sets Kp and Ki
             speedRegulator -> setKpAndKi(std::stod(data.substr(6,5)), std::stod(data.substr(11,5)));

             //Pulls the service brake if necessary
             if(data.substr(18,1) == "1") speedRegulator -> pullServiceBrake();

             //Pulls the emergency brake if necessary
             if(data.substr(19,1) == "1") speedRegulator -> pullEmergencyBrake();

             //If the resolve failure button is pushed, then set failure to 0 in both train model and speed regulator
             if(data.substr(20,1) == "1")
             {
                 trainModel -> setSystemFailure(0);
                 speedRegulator -> setFailureCode(0);
             }

             //Updates the headlights if the switch indicates it or the beacon indicates it and the mode is automatic
             if(data.substr(21,1) == "1" || (beacon -> getTurnHeadlightsOn() && mode -> getMode() == 0)) trainModel -> setHeadlights(1);
             else trainModel -> setHeadlights(0);

             //If the release brake button is pushed, release whichever brake was pulled
             if(data.substr(22,1) == "1")
             {
                 trainModel -> setServiceBrake(0);
                 trainModel -> setEmergencyBrake(0);
             }

             //Updates the right doors
             if(data.substr(23,1) == "1" || (!stopAlreadyOccurred && stopTimerStarted && trainModel -> getRightDoorStatus())) trainModel -> setRightDoorStatus(1);
             else trainModel -> setRightDoorStatus(0);

             //Updates the beacon information
             updateBeaconData(data.substr(21,1));

             //Updates power command
             speedRegulator -> calcPowerCmd();
           }
    }
}

void TrainController::updateBeaconData(std::string headlights)
{
    //Get the current beacon that is at the current block
    beacon -> setBeaconData(trainModel -> getBeaconData());

    //If the train is in automatic mode:
    if(mode -> getMode() == 0)
    {
        //Turn the headlights on if there is a tunnel upcoming
        if(beacon -> getTurnHeadlightsOn()) trainModel -> setHeadlights(1);

        //Keep the headlights on if there is not a tunnel upcoming, but the switch on the UI is on
        else if (!beacon -> getTurnHeadlightsOn() && headlights == "1")  trainModel -> setHeadlights(1);

        //Otherwise set the headlights to 0
        else trainModel -> setHeadlights(0);

        //Stop the train at the station if the train is at the station and has not already stopped
        if(beacon -> getStationHere() && !stopAlreadyOccurred)
        {
            //Pull the service brake
            speedRegulator -> pullServiceBrake();

            //Once the brake has been pulled, wait for the train to stop
            if(trainModel -> getCurrentVelocity() == 0 && stopTimerStarted == 0)
            {
                //Once the train has stopped, start the timer to wait at station
                stopTimerStarted = 1;
                start = systemClock -> currentTime();

                //Open the doors for the passengers to unload/load onto the train
                if(beacon -> getPlatformDoors() == "RIGHT") trainModel -> setRightDoorStatus(1);
                else if(beacon -> getPlatformDoors() == "LEFT") trainModel -> setLeftDoorStatus(1);
                else
                {
                    trainModel -> setRightDoorStatus(1);
                    trainModel -> setLeftDoorStatus(1);
                }
            }

            if(stopTimerStarted == 1)
            {
                //Update the current time
                now = systemClock -> currentTime();

                //If the train has been stopped for 60 seconds, release the service brake and set the stopTimerStarted flag back to 0 and the stopAlreadyOccurred flag to 1
                if(start.secsTo(now) >= 60)
                {
                    //Close the doors because the train is finished unloading/loading passeners
                    trainModel -> setRightDoorStatus(0);
                    trainModel -> setLeftDoorStatus(0);

                    //Release the service brake
                    trainModel -> setServiceBrake(0);

                    //Mark that the stop has already occurred in the block so it does not occur again
                    stopAlreadyOccurred = 1;
                }
            }
        }

        //Sets stop already occurred to 0 when there is not a station in the current block
        if(!beacon -> getStationHere())
        {
            stopAlreadyOccurred = 0;
            stopTimerStarted = 0;
        }
    }
}

void TrainController::writeData()
{

    //Create a system to encode all data to be returned to the interface in the string
      //char 0 = cabinLights
      //char 1 = cabinAc
      //char 2 = cabinHeat
      //char 3 = cabinDoorsLeftClosed
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
      //char 45 = cabinHeadlights
      //char 46 = mode
      //char 47 = cabinDoorsRightClosed
      //char 48-49 = platformSideChar
      //char 50-54 = stationCode
      //char 55 = stationUpcoming
      //char 56 = turnHeadlightsOn
      //char 57 = stationHere
      //char 58 = newine

    //Initialize the string to build the outgoing data upon
    string outgoing_s = "";

    //Add the cabin controls to the string
    outgoing_s += to_string(trainModel -> getCabinLights());
    outgoing_s += to_string(trainModel -> getAC());
    outgoing_s += to_string(trainModel -> getHeater());
    outgoing_s += to_string(trainModel -> getLeftDoorStatus());
    outgoing_s += to_string(trainModel -> getAdvertisements());
    outgoing_s += to_string(trainModel -> getAnnouncements());

    //Add the authority
    string authority(to_string(  (speedRegulator -> getAuthority()) ), 0, 5);
    outgoing_s += authority;

    while(outgoing_s.length() <= 10) outgoing_s += " ";

    //Add the proportional gain
    string Kp(to_string((speedRegulator -> getKp())/1000), 0, 5);
    outgoing_s += Kp;

    while(outgoing_s.length() <= 15) outgoing_s += " ";

    //Add the integral gain
    string Ki(to_string((speedRegulator -> getKi())/1000), 0, 5);
    outgoing_s += Ki;

    while(outgoing_s.length() <= 20) outgoing_s += " ";

    //Add the commanded speed
    string commandedSpeed( to_string(speedRegulator -> getCommandedSpeed() * 0.621371), 0, 5 ); //km/hr --> mi/hr
    outgoing_s += commandedSpeed;

    while(outgoing_s.length() <= 25) outgoing_s += " ";

    //Add the setpoint speed
    string setpointSpeed(to_string(speedRegulator -> getSetpointSpeed() * 0.621371), 0, 5); //km/hr --> mi/hr
    outgoing_s += setpointSpeed;

    while(outgoing_s.length() <= 30) outgoing_s += " ";

    //Add the current speed
    string currentSpeed(to_string( (trainModel -> getCurrentVelocity() ) * 2.23694), 0, 5); //m/s --> km/hr
    outgoing_s += currentSpeed;

    while(outgoing_s.length() <= 35) outgoing_s += " ";

    //Add the service brake
    outgoing_s+= to_string(trainModel -> getServiceBrake());

    //Add the service brake
    outgoing_s+= to_string(trainModel -> getEmergencyBrake());

    //Add the power
    string power(to_string(trainModel -> getPower()/1000), 0, 6);
    outgoing_s += power;
    while(outgoing_s.length() <= 43) outgoing_s += " ";

    //Add the failure code
    outgoing_s += to_string(speedRegulator -> getFailureCode());

    //Add the headlights
    outgoing_s += to_string(trainModel -> getHeadlights());

    //Add the mode
    outgoing_s += to_string(mode -> getMode());

    //Add the right door status
    outgoing_s += to_string(trainModel -> getRightDoorStatus());

    //Add the ascii code of the character (R, L, B) for the side of the platform to open
    outgoing_s += to_string(beacon -> getPlatformDoorsChar());
    while(outgoing_s.length() <= 49) outgoing_s += " ";

    //Add the 5-digit station code for the next station
    outgoing_s += beacon -> getStationCode();
    while(outgoing_s.length() <= 54) outgoing_s += " ";

    //Add the upcoming station flag
    outgoing_s += to_string(beacon -> getStationUpcoming());

    //Add the headlights flag
    outgoing_s += to_string(beacon -> getTurnHeadlightsOn());

    //Add the station here flag
    outgoing_s += to_string(beacon -> getStationHere());

    //Add the newline character
    outgoing_s += "\n";

    std::cout << "Outgoing: " << outgoing_s << std::endl;
    std::cout << "Outgoing Length: " << outgoing_s.length() << std::endl;

    //Convert the string to a character array
    strcpy(outgoingData, outgoing_s.c_str());

    //Write the character array to the serial port
    trainControllerPort.writeString(outgoing_s);
}

Train* TrainController::getTrainModel()
{
    return trainModel;
}
SpeedRegulator* TrainController::getSpeedRegulator()
{
    return speedRegulator;
}
BeaconDecoder* TrainController::getBeaconDecoder()
{
    return beacon;
}
CTCMode* TrainController::getCTCMode()
{
    return mode;
}

void TrainController::receiveDataSim(string data)
{
    if(data.length() == 26)
    {
         //Updates the cabin lights
         if(data.substr(0,1) == "1") trainModel -> setCabinLights(1);
         else trainModel -> setCabinLights(0);

         //Updates the air conditioning
         if(data.substr(1,1) == "1") trainModel -> setAC(1);
         else trainModel -> setAC(0);

         //Updates the heater
         if(data.substr(2,1) == "1") trainModel -> setHeater(1);
         else trainModel -> setHeater(0);

         //Updates the left doors
         if(data.substr(3,1) == "1" || (!stopAlreadyOccurred && stopTimerStarted && trainModel -> getLeftDoorStatus())) trainModel -> setLeftDoorStatus(1);
         else trainModel -> setLeftDoorStatus(0);

         //Updates the advertisements
         if(data.substr(4,1) == "1") trainModel -> setAdvertisements(1);
         else trainModel -> setAdvertisements(0);

         //Updates the announcements
         if(data.substr(5,1) == "1") trainModel -> setAnnouncements(1, beacon -> getAnnouncement());
         else trainModel -> setAnnouncements(0,beacon->getAnnouncement());

         //Increments the setpoint speed if the joystick indicates
         if(data.substr(16,1) == "1") speedRegulator -> incSetpointSpeed(5);

         //Decrements the setpoint speed if the joystick indicates
         if(data.substr(17,1) == "1") speedRegulator -> incSetpointSpeed(-5);

         //Sets Kp and Ki
         speedRegulator -> setKpAndKi(std::stod(data.substr(6,5)), std::stod(data.substr(11,5)));

         //Pulls the service brake if necessary
         if(data.substr(18,1) == "1") speedRegulator -> pullServiceBrake();

         //Pulls the emergency brake if necessary
         if(data.substr(19,1) == "1") speedRegulator -> pullEmergencyBrake();

         //If the resolve failure button is pushed, then set failure to 0 in both train model and speed regulator
         if(data.substr(20,1) == "1")
         {
             trainModel -> setSystemFailure(0);
             speedRegulator -> setFailureCode(0);
         }

         //Updates the headlights if the switch indicates it or the beacon indicates it and the mode is automatic
         if(data.substr(21,1) == "1" || (beacon -> getTurnHeadlightsOn() && mode -> getMode() == 0)) trainModel -> setHeadlights(1);
         else trainModel -> setHeadlights(0);

         //If the release brake button is pushed, release whichever brake was pulled
         if(data.substr(22,1) == "1")
         {
             trainModel -> setServiceBrake(0);
             trainModel -> setEmergencyBrake(0);
         }

         //Updates the right doors
         if(data.substr(23,1) == "1" || (!stopAlreadyOccurred && stopTimerStarted && trainModel -> getRightDoorStatus())) trainModel -> setRightDoorStatus(1);
         else trainModel -> setRightDoorStatus(0);

         //Updates the beacon information
         updateBeaconData(data.substr(21,1));

         //Updates power command
         speedRegulator -> calcPowerCmd();
       }
}
std::string TrainController::writeDataSim()
{
    //Initialize the string to build the outgoing data upon
    string outgoing_s = "";

    //Add the cabin controls to the string
    outgoing_s += to_string(trainModel -> getCabinLights());
    outgoing_s += to_string(trainModel -> getAC());
    outgoing_s += to_string(trainModel -> getHeater());
    outgoing_s += to_string(trainModel -> getLeftDoorStatus());
    outgoing_s += to_string(trainModel -> getAdvertisements());
    outgoing_s += to_string(trainModel -> getAnnouncements());

    //Add the authority
    string authority(to_string(  (speedRegulator -> getAuthority()) ), 0, 5);
    outgoing_s += authority;

    while(outgoing_s.length() <= 10) outgoing_s += " ";

    //Add the proportional gain
    string Kp(to_string((speedRegulator -> getKp())/1000), 0, 5);
    outgoing_s += Kp;

    while(outgoing_s.length() <= 15) outgoing_s += " ";

    //Add the integral gain
    string Ki(to_string((speedRegulator -> getKi())/1000), 0, 5);
    outgoing_s += Ki;

    while(outgoing_s.length() <= 20) outgoing_s += " ";

    //Add the commanded speed
    string commandedSpeed( to_string(speedRegulator -> getCommandedSpeed() * 0.621371), 0, 5 ); //km/hr --> mi/hr
    outgoing_s += commandedSpeed;

    while(outgoing_s.length() <= 25) outgoing_s += " ";

    //Add the setpoint speed
    string setpointSpeed(to_string(speedRegulator -> getSetpointSpeed() * 0.621371), 0, 5); //km/hr --> mi/hr
    outgoing_s += setpointSpeed;

    while(outgoing_s.length() <= 30) outgoing_s += " ";

    //Add the current speed
    string currentSpeed(to_string( (trainModel -> getCurrentVelocity() ) * 2.23694), 0, 5); //m/s --> km/hr
    outgoing_s += currentSpeed;

    while(outgoing_s.length() <= 35) outgoing_s += " ";

    //Add the service brake
    outgoing_s+= to_string(trainModel -> getServiceBrake());

    //Add the service brake
    outgoing_s+= to_string(trainModel -> getEmergencyBrake());

    //Add the power
    string power(to_string(trainModel -> getPower()/1000), 0, 6);
    outgoing_s += power;
    while(outgoing_s.length() <= 43) outgoing_s += " ";

    //Add the failure code
    outgoing_s += to_string(speedRegulator -> getFailureCode());

    //Add the headlights
    outgoing_s += to_string(trainModel -> getHeadlights());

    //Add the mode
    outgoing_s += to_string(mode -> getMode());

    //Add the right door status
    outgoing_s += to_string(trainModel -> getRightDoorStatus());

    //Add the ascii code of the character (R, L, B) for the side of the platform to open
    outgoing_s += to_string(beacon -> getPlatformDoorsChar());
    while(outgoing_s.length() <= 49) outgoing_s += " ";

    //Add the 5-digit station code for the next station
    outgoing_s += beacon -> getStationCode();
    while(outgoing_s.length() <= 54) outgoing_s += " ";

    //Add the upcoming station flag
    outgoing_s += to_string(beacon -> getStationUpcoming());

    //Add the headlights flag
    outgoing_s += to_string(beacon -> getTurnHeadlightsOn());

    //Add the station here flag
    outgoing_s += to_string(beacon -> getStationHere());


    return outgoing_s;
}
