#pragma once

#include <iostream>
#include <vector>
#include "TrackController.h"

class CTCSignals : private TrackController
{
    private:
        void setFlag(bool);
    public:
        bool update_flag = 0;
        void setSignal(float[], float[]);
        std::vector<float> ctc_spd;
        std::vector<float> ctc_auth;
};
