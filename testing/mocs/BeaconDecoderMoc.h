#ifndef BEACONDECODERMOC_H
#define BEACONDECODERMOC_H

#include <string>
#include <cstdint>
#include "../../TrackModel/trackmodel_types.hpp"
using namespace TrackModel;

class BeaconDecoderMoc
{
    private:
        BeaconData beacon;
        std::string nextStation;
        bool stationUpcoming;
        bool turnHeadlightsOn;
        bool stationHere;
        char platformDoorsChar;
        std::string platformDoors;
        std::string stationCode;

    public:

        //Constructor
        BeaconDecoderMoc();

        //Set address of BeaconData struct
        void setBeaconData(BeaconData b);

        //Method to decode the beacon data
        void extractBeaconData();

        //Method to generate an announcement from the beacon data
        std::string getAnnouncement();

        //Accessor Functinons
        std::string getNextStation();
        char getPlatformDoorsChar();
        bool getTurnHeadlightsOn();
        bool getStationUpcoming();
        bool getStationHere();
        std::string getPlatformDoors();
        std::string getStationCode();
};

#endif // BEACONDECODERMOC_H
