#ifndef BEACONDECODER_H
#define BEACONDECODER_H

#include <string>
#include <cstdint>
#include "../TrackModel/trackmodel_main.hpp"
#include "../TrackModel/trackmodel_types.hpp"

using namespace TrackModel;

class BeaconDecoder
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

        /*!
            Constructor that initializes all of the member variables
            @pre: none
            @post: a BeaconDecoder object is created with initialized variables
            @param: none
            @throw: none
            @return: none
        */
        BeaconDecoder();

        /*!
            Method that copies a BeaconData object into the BeaconData member variable
            @pre: the BeaconData object in the parameters is preinitialized with values
            @post: beacon has new values for each BeaconData parameter
            @param: a BeaconData object to be copied into beacon
            @throw: none
            @return: none
        */
        //Set address of BeaconData struct
        void setBeaconData(BeaconData b);

        /*!
            Method that extracts information from the beacon member variable and places
            the proper pieces of information in the appropriate member variables
            @pre: a BeaconDecoder object is created with initialized variables
            @post: the member variables are updated to reflect the current beacon values
            @param: none
            @throw: none
            @return: none
        */
        void extractBeaconData();

        /*!
            Method that uses nextStation and platformSide to generate and annoucnement
            to broadcast on the train
            @pre: a BeaconDecoder object has nextStation and platformSide initialized
            @post: announcement is returned with updated station and platform information
            @param: none
            @throw: none
            @return: a string holding the announcement to broadcast on the train
        */
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

#endif // BEACONDECODER_H
