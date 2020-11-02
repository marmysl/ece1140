#include "BeaconDecoderMoc.h"

BeaconDecoderMoc::BeaconDecoderMoc()
{
    //Initialize the member variables to 0
    nextStation = "";
    distanceToStation = 0;
}

//Method to decode the beacon data
void BeaconDecoderMoc::decodeBeacon(uint8_t data[64])
{
    //Assuming:
    //data[1] and data[0] = next station
    //data[3] and data[2] = distance

    //Decode the distance to the next station
    nextStation = std::to_string(data[1]) + std::to_string(data[0]);
    distanceToStation = 5;
}

//Method to generate an announcement from the beacon data
std::string BeaconDecoderMoc::getAnnouncement()
{
    return "The next station is " + nextStation + ". Thank you for choosing Port Authority.";
}
