//This file contains a class declaration
#ifndef TrackController_h
#define TrackController_h

#include "CTCSignals.h"
#include "BlockCntrl.h"
#include "tracklogic.h"
#include <vector>
#include <string>


class TrackController
{
	
	public:
        CTCSignals ctc_wayside;
        TrackLogic PLC;
        std::string filename;
        std::vector<BlockCntrl> blocks;
        int region;
        std::string line;
        std::vector<char> cntrl_sections;
        std::vector<int> cntrl_blocks;
        int switch_head;
        int switch_tail0;
        int switch_tail1;
        bool switch_state;
        int crossing_id;
        bool route;
        int start_block;
        int block_count;

        std::vector<float> CTC_sugspeed;
        std::vector<int> CTC_sugauth;

        TrackController();
        void setUpController(int, std::string &, std::vector<char> &, std::vector<int> &, int[], int);
        void setSignalsInstance(CTCSignals &);
        void setSwitch(bool);
        void addBlockObj(int);
        void setSpdAuth();
        void setRoute();
		int getResult();
};

#endif /*TrackController_h*/
