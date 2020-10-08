#include <iostream>
#include "TrackController.hpp"
#include "TrackController.cpp"

int main() {

    TrackController tc1; 

    return 0;
}

// #include <iostream>
// #include <string>
// #include "SerialPort.hpp"
// #include "SerialPort.cpp"
// #include <stdio.h>
// #include <vector>

// // Other 
// #include "CTCDispatch.h"
// #include "CTCDispatch.cpp"
// #include "../TrackModel/tracklayout.hpp"
// #include "../TrackModel/trackmodel_controller.hpp"
// #include "../TrackModel/trackmodel_test.hpp"

// // My files :)
// #include "Region.hpp"
// #include "Region.cpp"
// #include "CTCSignals.hpp"
// #include "FailureDetector.cpp"
// #include "Track.cpp"

// using namespace std;

// char portName[] = "\\\\.\\COM3";

// char incomingData[255];
// char outgoingData[255];

// //Arduino SerialPort object
// SerialPort *arduino;

// // My objects
// CTCDispatch d1;
// Region r1;
// CTCSignals c1;
// Track t1(r1);

// //If you want to send data then define "SEND" else comment it out
// #define SEND

// void ReceiveData(void)
// {
//     int readResult = arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
//     string data(incomingData);

//     // Data received from the GUI
//     /*
//      * Manual Switch : 0 or 1
//      * Railway Switches Switch : 0 or 1
//      * Railway Crossing Switch : 0 or 1
//      * Color of the Lights : 00, 01, 10 - Green, Yellow, Red
//      * State of the PLC Button: 0 or 1
//      * State of the View Track Button: 0 or 1
//      * Joystick Left: 0 or 1
//      * Joystick Right: 0 or 1
//      * Joystick Up: 0 or 1
//      * Joystick Down: 0 or 1
//      */

//     // Currently implemented: Joystick L R U D

//     std::cout << "Incoming: " << data << std::endl;

//     if(!data.empty())
//     {
//         if(data.substr(0,1) == "1") {
//             if (r1.getCurrentBlock() == 1) {
//                 r1.setCurrentBlock(15);
//             } else {
//                  r1.setCurrentBlock(r1.getCurrentBlock() - 1);
//             }
//         }

//         if(data.substr(1,1) == "1") {
//             if (r1.getCurrentBlock() == 15) {
//                 r1.setCurrentBlock(1);
//             } else {
//                  r1.setCurrentBlock(r1.getCurrentBlock() + 1);
//             }
//         }  

//         if(data.substr(2,1) == "1") {
//             r1.setSection(r1.getSection());
//         }

//         if(data.substr(3) == "1") {
//             r1.setSection(r1.getSection());
//         }

//     }  
//     Sleep(100);
// }

// void WriteData(unsigned int delayTime)
// {
//     // Data that needs to be sent to the GUI
//     /*
//      * Block Occupancy
//      * Current Section
//      * Current Block
//      * Suggested Speed
//      * Commanded Speed
//      * Authority
//      * Lights color
//      */

//     string outgoing_s = "";

//     outgoing_s += std::to_string(t1.detectTrain());
//     outgoing_s += r1.getSection();
//     outgoing_s += std::to_string(r1.getCurrentBlock());
//     outgoing_s += std::to_string(r1.getSuggestedSpeed());
//     outgoing_s += std::to_string(r1.getCommandedSpeed());
//     outgoing_s += std::to_string(r1.getAuthority());
//     outgoing_s += std::to_string(t1.getLights());

//     outgoing_s += "\n";

//     std::cout << "Outgoing Data to Arduino: " << outgoing_s << std::endl;
//     strcpy(outgoingData, outgoing_s.c_str());

//     arduino->writeSerialPort(outgoingData, MAX_DATA_LENGTH);
//     Sleep(delayTime);
// }

// void autoConnect(void)
// {
//         std::cout << "Searching in progress";
//         // wait connection
//         while (!arduino->isConnected()) {
//             Sleep(100);
//             std::cout << ".";
//             arduino = new SerialPort(portName);
//         }

//         //Checking if arduino is connected or not
//         if (arduino->isConnected()) {
//             std::cout  << std::endl << "Connection established at port " << portName << std::endl;
//         }
// }

// int main()
// {
//     arduino = new SerialPort(portName);

//     autoConnect();

//     d1.setStation("Station B");
//     d1.setTimeStart("10:00");
//     d1.setTimeArrival("12:00");
//     d1.dispatch(c1);
//     r1.initialize(c1);
//     t1.detectTrain();
//     t1.updateLights();

//     while(arduino -> isConnected())
//     {
//         ReceiveData();
//         cout << r1.getCurrentBlock() << " Current Block is it changing" << endl;
//         WriteData(250);
//     }
// }


