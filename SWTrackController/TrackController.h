//This file contains a class declaration
#ifndef TrackController_h
#define TrackController_h

#include "CTCSignals.h"
#include "BlockCntrl.h"
#include "tracklogic.h"
#include "../TrackModel/tracklayout.hpp"
#include "../TrackModel/trackmodel_controller.hpp"
#include "../TrackModel/trackmodel_main.hpp"
#include <vector>
#include <string>


class TrackController
{
	
	public:
        CTCSignals ctc_wayside;
        TrackLogic PLC;
        std::vector<BlockCntrl> blocks;


        std::string filename, plcfile1, plcfile2;
        int wayside_id;
        std::string line;

        std::vector<char> cntrl_sections;
        std::vector<int> cntrl_blocks;
        bool initialized_ctcstruct;

        int switch_head;
        int switch_tail0;
        int switch_tail1;
        bool switch_state;

        int crossing_id;
        bool cross_state;

        int ctc_exit_id;
        int exit_block0;
        int exit_block1;
        bool hold_exit;
        int start_block;
        int block_count;

        float CTC_sugspeed;
        std::vector<std::pair< int, int> > CTC_sugauth;

        std::vector<float> CTC_tempspeed;
        std::vector<int> CTC_tempauth;

        std::vector<float> CTC_comspeed;
        std::vector<int> CTC_comauth;

        std::vector<std::pair< int, int> > faults_vect;
        std::vector<std::pair< int, bool> > occ_vect;

        TrackController();
        void setUpController(int, std::string &, std::vector<char> &, std::vector<int> &, int[], int, int[]);
        void setSignalsInstance(CTCSignals &);
        void setSwitch(bool);
        void setSwitchAuto();
        void addBlockObj(int);
        void setTrackSA();
        void setRoute();
		int getResult();
        void setCross();
        void manSetCross(bool);
        void getFaults();
        void getOccupancies();
        void updateData();
};

#endif /*TrackController_h*/
