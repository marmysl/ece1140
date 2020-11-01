#ifndef BEACONDECODERMOC_H
#define BEACONDECODERMOC_H

#include <string>
#include <cstdint>

class BeaconDecoderMoc
{
    private:
        std::string nextStation;
        double distanceToStation;

    public:

        //Constructor
        BeaconDecoderMoc();

        //Method to decode the beacon data
        void decodeBeacon(uint8_t data[64]);

        //Method to generate an announcement from the beacon data
        std::string getAnnouncement();

        //Accessor Functinons
        std::string getNextStation();
        double getDistanceToStation();

};

#endif // BEACONDECODERMOC_H
