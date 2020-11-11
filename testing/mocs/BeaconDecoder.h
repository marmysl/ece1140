#ifndef BEACONDECODER_H
#define BEACONDECODER_H

#include <string>
#include <cstdint>

class BeaconDecoder
{
    private:
        std::string nextStation;
        double distanceToStation;

    public:

        //Constructor
        BeaconDecoder();

        //Method to decode the beacon data
        void decodeBeacon(uint8_t data[64]);

        //Method to generate an announcement from the beacon data
        std::string getAnnouncement();

        //Accessor Functinons
        std::string getNextStation();
        double getDistanceToStation();

};

#endif // BEACONDECODER_H
