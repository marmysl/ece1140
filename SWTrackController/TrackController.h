//This file contains a class declaration
#ifndef TrackController_h
#define TrackController_h

#include "CTCSignals.h"
#include "BlockCntrl.h"
#include "tracklogic.h"
#include <vector>
#include <string>

//int init_SWTrackController();

//FlashLight class declaration
class TrackController
{
	
	public:
        CTCSignals ctc_wayside;
        TrackLogic PLC;
        std::vector<BlockCntrl> blocks;
        int region;
        std::string line;
        std::vector<char> cntrl_sections;
        std::vector<int> cntrl_blocks;
        std::vector<int> cntrl_switches;
        int dest_block;
        int start_block;
		int block_count;
		int section_length;
		int section_count;

        TrackController();
        void setUpController(int, std::string &, std::vector<char> &, std::vector<int> &);
        void setSignalsInstance(CTCSignals &);
        void addBlockObj(int);
        void setSpdAuth();
        void setRoute();
		int getResult();
};

#endif /*TrackController_h*/
