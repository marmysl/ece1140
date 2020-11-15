#include "BeaconDecoder.h"

BeaconDecoder::BeaconDecoder()
{
    //Initialize the beacon data with default values
    nextStation = "";
    stationUpcoming = 0;
    turnHeadlightsOn = 0;
    platformDoors = "";
    stationCode = "";
}

//Method to decode the beacon data
void BeaconDecoder::extractBeaconData()
{
    //Next station
    //nextStation = beacon -> stationName;

    //Whether or not there is a station in the next block
    //stationUpcoming = beacon -> stationUpcoming;

    //Indicates whether the headlights should be on or off
    //turnHeadlightsOn = beacon -> newLightState;

    //Indicates whether the train should open the doors on the left or right side
    //platformDoorsChar = beacon -> platformSide;
}

//Method to generate an announcement from the beacon data
std::string BeaconDecoder::getAnnouncement()
{
    std::string announcement = "";
    if(getPlatformDoors() == "LEFT") announcement = "The next station is " + nextStation + ". Please exit on your left.";
    else if(getPlatformDoors() == "RIGHT") announcement  = "The next station is " + nextStation + ". Please exit on your right";
    else announcement = "The next station is " + nextStation + ". Please exit on either side.";
    return announcement;
}

//Method to set address of the BeaconData
/*
void setBeaconDataAddress(BeaconData* b)
{
    beacon = b;
    extractBeaconData();
}
*/

std::string BeaconDecoder::getStationCode()
{
    //Returns the station code to send to the arduino
    if(nextStation == "SHADYSIDE") stationCode = "00000";
    else if(nextStation == "HERRON AVE") stationCode = "00001";
    else if(nextStation == "SWISSVILLE") stationCode = "00010";
    else if(nextStation == "PENN STATION") stationCode = "00011";
    else if(nextStation == "STEEL PLAZA") stationCode = "00100";
    else if(nextStation == "FIRST AVE") stationCode = "00101";
    else if(nextStation == "STATION SQUARE") stationCode = "00110";
    else if(nextStation == "SOUTH HILLS JUNCTION") stationCode = "00111";
    else if(nextStation == "PIONEER") stationCode = "01000";
    else if(nextStation == "EDGEBROOK") stationCode = "01001";
    else if(nextStation == "WHITED") stationCode = "01010";
    else if(nextStation == "SOUTH BANK") stationCode = "01011";
    else if(nextStation == "CENTRAL") stationCode = "01100";
    else if(nextStation == "INGLEWOOD") stationCode = "01101";
    else if(nextStation == "OVERBROOK") stationCode = "01110";
    else if(nextStation == "GLENBURY") stationCode = "01111";
    else if(nextStation == "DORMONT") stationCode = "10000";
    else if(nextStation == "MT. LEBANON") stationCode = "10001";
    else if(nextStation == "POPLAR") stationCode = "10010";
    else if(nextStation == "CASTLE SHANNON") stationCode = "10011";
    else stationCode = "11111";

    return stationCode;
}

std::string BeaconDecoder::getNextStation()
{
    extractBeaconData();
    return nextStation;
}

char BeaconDecoder::getPlatformDoorsChar()
{
    extractBeaconData();
    return platformDoorsChar;
}

bool BeaconDecoder::getTurnHeadlightsOn()
{
    extractBeaconData();
    return turnHeadlightsOn;
}

bool BeaconDecoder::getStationUpcoming()
{
    extractBeaconData();
    return stationUpcoming;
}

std::string BeaconDecoder::getPlatformDoors()
{
    extractBeaconData();
    if(platformDoorsChar == 'B') platformDoors = "BOTH";
    else if(platformDoorsChar == 'L') platformDoors = "LEFT";
    else platformDoors = "RIGHT";

    return platformDoors;
}

