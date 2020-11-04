//This file contains a class declaration
#ifndef TrackController_h
#define TrackController_h

#include "CTCOffice/ctcoffice/CTCSignals.h"
#include <vector>
#include <string>

//int init_SWTrackController();

//FlashLight class declaration
class TrackController
{
	
	public:
        CTCSignals ctc_wayside;
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
        void setUpController(int, std::vector<char> &, std::vector<int> &);
        void setSignalsInstance(CTCSignals &);
		int getResult();
};

#endif /*TrackController_h*/
