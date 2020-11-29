//ADD GUARD
#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

#include <iostream>
#include <vector>
#include "Region.hpp"

class CTCSignals
{
public:
    float speedCTC;
    int authCTC;
    int routeCTC;
    void setSignal(float s, int a, int r);
    float getSpeed();
    float getAuth();
    int getDestBlock();
//    bool getOccupancy(int blockNum);
};

//END GUARD
#endif
