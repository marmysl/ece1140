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
#include "../../TrackModel/trackrouter.h"

class CTCDispatch
{
    private:
        std::string line;
        int endblock;
        std::string station;
        float timeStart = 0;
        float timeArrival = 0;
        float passNum;
        int carsNum;
        CTCMode* m = nullptr;
    public:


        std::vector<float> authority;
        float speed;
        std::vector<bool> tcStates;
        void setAuthority();
        void setSpeed(float, float);
        void sendTrackController(CTCSignals &);
        void dispatch(CTCSignals &);

        void setLine(std::string);
        std::string getline();
        void setDestination(QString, QString);
        void setStation(std::string);
        std::string getStation();
        void setBlock(int);
        int getBlock();
        void setTimeStart(std::string);
        float getTimeStart();
        void setTimeArrival(std::string);
        float getTimeArrival();
        void setPassNum();
        float getPassNum();
        void setCTCMode(CTCMode*);
        CTCMode* getCTCMode();
        TrackModel::TrainPathInfo  findRoute();
};

#endif // CTCDISPATCH_H
