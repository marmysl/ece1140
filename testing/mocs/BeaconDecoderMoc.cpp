#include "BeaconDecoderMoc.h"
#include <iostream>

BeaconDecoderMoc::BeaconDecoderMoc()
{
    //Initialize the beacon data with default values
    nextStation = "IN YARD";
    stationUpcoming = 0;
    turnHeadlightsOn = 0;
    stationHere = 0;
    platformDoors = "BOTH";
    stationCode = "11111";
    platformDoorsChar = 'B';

    //Create a placeholder beaconData until the train model sends a new object
    BeaconData placeholder;
    placeholder.stationName = "IN YARD";
    beacon = placeholder;
}

//Method to decode the beacon data
void BeaconDecoderMoc::extractBeaconData()
{
    if(beacon.hasData())
    {
        //Next station
        nextStation = beacon.stationName;

        //Station code based on the next station
        stationCode = getStationCode();

        //Whether or not there is a station in the next block
        stationUpcoming = beacon.stationUpcoming;

        //Indicates whether the headlights should be on or off
        turnHeadlightsOn = beacon.newLightState;

        //Indicates if the station is here
        stationHere = beacon.stationHere;

        //Indicates whether the train should open the doors on the left or right side
        platformDoorsChar = beacon.platformSide;

    }
    else
    {
        //Set station here, turn headlights on, and station upcoming to 0
        turnHeadlightsOn = 0;
        stationHere = 0;
        stationUpcoming = 0;

        //Keep station name the same so the announcements can tell the user the next announcement coming
    }
}

std::string BeaconDecoderMoc::getAnnouncement()
{
    //Initialize a string for the annoucnement to be stored in
    std::string announcement = "";

    if(stationUpcoming || stationHere)
    {

        //If the station is on the left, tell passengers to exit on the left
        if(getPlatformDoors() == "LEFT") announcement = "The next station is " + nextStation + ". Please exit on your left.";

        //If the station is on the left, tell passengers to exit on the left
        else if(getPlatformDoors() == "RIGHT") announcement  = "The next station is " + nextStation + ". Please exit on your right.";

        //If the station is on the left, tell passengers to exit on the left
        else announcement = "The next station is " + nextStation + ". Please exit on either side.";

    }
    else
    {
        announcement = "Thank you for choosing Port Authority.";
    }

    //Return the full announcement
    return announcement;
}

//Method to set address of the BeaconData
void BeaconDecoderMoc::setBeaconData(BeaconData b)
{
    beacon = b;
    extractBeaconData();
}

std::string BeaconDecoderMoc::getStationCode()
{
    //Returns the station code to send to the arduino
    if(nextStation == "ShadySide") stationCode = "00000";
    else if(nextStation == "Herron Ave") stationCode = "00001";
    else if(nextStation == "Swissville") stationCode = "00010";
    else if(nextStation == "Penn Station") stationCode = "00011";
    else if(nextStation == "Steel Plaza") stationCode = "00100";
    else if(nextStation == "First Ave") stationCode = "00101";
    else if(nextStation == "Station Square") stationCode = "00110";
    else if(nextStation == "South Hills Junction") stationCode = "00111";
    else if(nextStation == "Pioneer") stationCode = "01000";
    else if(nextStation == "Edgebrook") stationCode = "01001";
    else if(nextStation == "Whited") stationCode = "01010";
    else if(nextStation == "South Bank") stationCode = "01011";
    else if(nextStation == "Central") stationCode = "01100";
    else if(nextStation == "Inglewood") stationCode = "01101";
    else if(nextStation == "Overbrook") stationCode = "01110";
    else if(nextStation == "Glenbury") stationCode = "01111";
    else if(nextStation == "Dormont") stationCode = "10000";
    else if(nextStation == "Mt Lebanon") stationCode = "10001";
    else if(nextStation == "Poplar") stationCode = "10010";
    else if(nextStation == "Castle Shannon") stationCode = "10011";
    else stationCode = "11111";

    return stationCode;
}

std::string BeaconDecoderMoc::getNextStation()
{
    extractBeaconData();
    return nextStation;
}

char BeaconDecoderMoc::getPlatformDoorsChar()
{
    extractBeaconData();
    return platformDoorsChar;
}

bool BeaconDecoderMoc::getTurnHeadlightsOn()
{
    extractBeaconData();
    return turnHeadlightsOn;
}

bool BeaconDecoderMoc::getStationUpcoming()
{
    extractBeaconData();
    return stationUpcoming;
}
bool BeaconDecoderMoc::getStationHere()
{
    extractBeaconData();
    return stationHere;
}

std::string BeaconDecoderMoc::getPlatformDoors()
{
    extractBeaconData();
    if(platformDoorsChar == '\x00') platformDoors = "BOTH";
    else if(platformDoorsChar == '\xff') platformDoors = "LEFT";
    else platformDoors = "RIGHT";

    return platformDoors;
}

