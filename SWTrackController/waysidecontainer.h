#ifndef WAYSIDECONTAINER_H
#define WAYSIDECONTAINER_H

#include "trackcntrl_main.h"
#include "TrackController.h"
#include "BlockCntrl.h"
#include "CTCSignals.h"
#include <vector>

class WaysideContainer
{
public:
    WaysideContainer();
    std::vector<TrackController> waysides;
    void addTrackObj(int, std::string &, std::vector<char> &, std::vector<int> &);


    //Block Container of Wayside, within Track Controller class
    //commented for reference:
        //std::vector<BlockCntrl> blocks;
        //void addBlockObj(int num);

    //CTC Signals Container for Wayside
    CTCSignals wayside_signals;
    void addCTCObj(CTCSignals &);
};

#endif // WAYSIDECONTAINER_H
