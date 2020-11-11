#ifndef CTCDISPATCH_H
#define CTCDISPATCH_H

#include <vector>
#include <iostream>
#include <string>
//#include "../../SWTrackController/CTCSignals.h"
#include "../../SWTrackController/CTCSignals.h"
#include "../../TrackModel/tracklayout.hpp"
#include "../../SWTrackController/trackcntrl_main.h"
#include "../../HWTrackController/HWTrackController_main.h"
#include "CTCMode.h"


class CTCDispatch
{
    private:
        std::string line;
        std::string destinationType;
        int endblock;
        std::string station;
        float timeStart;
        float timeArrival;
        CTCMode* m = nullptr;
    public:


        std::vector<float> authority;
        std::vector<float> speed;
        void setAuthority(std::string, int);
        void setSpeed(std::string, int, float, float);
        void sendTrackController(CTCSignals &);
        void dispatch(CTCSignals &);

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
        void setCTCMode(CTCMode*);
        CTCMode* getCTCMode();
};

#endif // CTCDISPATCH_H
