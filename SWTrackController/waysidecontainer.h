#ifndef WAYSIDECONTAINER_H
#define WAYSIDECONTAINER_H

#include "TrackController.h"
#include "BlockCntrl.h"
#include <vector>

class WaysideContainer
{
public:
    WaysideContainer();
    std::vector<TrackController> waysides;
    void addTrackObj(int, std::vector<char> &, std::vector<int> &);


    //Block Container of Wayside
    std::vector<BlockCntrl> blocks;
    void addBlockObj(int num);
};

#endif // WAYSIDECONTAINER_H
