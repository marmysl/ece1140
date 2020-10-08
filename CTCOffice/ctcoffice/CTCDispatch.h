#ifndef CTCDISPATCH_H
#define CTCDISPATCH_H

#include <vector>
#include <iostream>
#include <string>
//#include "../../SWTrackController/CTCSignals.h"
#include "CTCSignals.h"
#include "../../TrackModel/tracklayout.hpp"

class CTCDispatch
{
    private:
        std::string line;
        std::string destinationType;
        int endblock;
        std::string station;
        float timeStart;
        float timeArrival;
    public:
        std::vector<float> authority;
        std::vector<float> speed;
        void setAuthority(std::string, int);
        void setSpeed(std::string, int, float, float);
        void sendTrackController(CTCSignals &c);
        void dispatch(CTCSignals &c);

        void setLine(std::string);
        std::string getline();
        void setDestinationType(std::string);
        std::string getDestinationType();
        void setStation(std::string);
        std::string getStation();
        void setBlock(std::string);
        int getBlock();
        void setTimeStart(std::string);
        float getTimeStart();
        void setTimeArrival(std::string);
        float getTimeArrival();
};

#endif // CTCDISPATCH_H
