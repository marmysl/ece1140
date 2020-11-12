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
        int last_block[2];
        bool route;
        int start_block;
        int block_count;
		int section_length;
		int section_count;
        int switch_id[4];
        int crossing_id;
        std::vector<float> CTC_sugspeed;
        std::vector<int> CTC_sugauth;

        TrackController();
        void setUpController(int, std::string &, std::vector<char> &, std::vector<int> &, int[4], int, int[2]);
        void setSignalsInstance(CTCSignals &);
        void addBlockObj(int);
        void setSpdAuth();
        void setRoute();
		int getResult();
};

#endif /*TrackController_h*/
