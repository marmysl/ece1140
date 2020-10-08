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
        std::string station;
        float timeStart;
        float timeArrival;
    public:
        std::vector<float> authority;
        std::vector<float> speed;
        void setAuthority(std::string);
        void setSpeed(std::string, float, float);
        void sendTrackController();
        void dispatch();

        void setLine(std::string);
        std::string getline();
        void setStation(std::string);
        std::string getStation();
        void setTimeStart(std::string);
        float getTimeStart();
        void setTimeArrival(std::string);
        float getTimeArrival();
};

#endif // CTCDISPATCH_H
