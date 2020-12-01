//This file contains the definitions of the member functions.
#include <iostream>
#include <vector>
#include "TrackController.h"
#include "waysidecontainer.h"

//using namespace std;

TrackController::TrackController(){
    switch_head = -1;
    switch_tail0 = -1;
    switch_tail1 = -1;
    switch_state = false;

    crossing_id = -1;
    cross_state = false;

    exit_block0 = -1;
    exit_block1 = -1;
    start_block = -1;

    block_count = 0;
    initialized_ctcstruct = false;

}

void TrackController::setUpController(int id, std::string &l, std::vector<char> &s, std::vector<int> &b, int sw[], int cr, int fin[]) {

    wayside_id = id;
    line = l;

    switch_head = sw[0];
    switch_tail0 = sw[1];
    switch_tail1 = sw[2];
    switch_state = sw[3];

    exit_block0 = fin[0];
    exit_block1 = fin[1];


    if (cr != 0) {
        crossing_id = cr;
    }
    else {
        crossing_id = -1;
    }

    auto m = b.begin();
    start_block = *m;

    for (auto i = s.begin(); i != s.end(); i++) {
        cntrl_sections.push_back(*i);
    }

    block_count = 0;
    for (auto i = b.begin(); i != b.end(); i++) {
        cntrl_blocks.push_back(*i);
        addBlockObj(*i);
        block_count++;
    }

    TrackLogic temp(sw, crossing_id);

}

void TrackController::addBlockObj(int num) {
    //using namespace std;
    BlockCntrl b;

    int temp_sw[4] = {switch_head, switch_tail0, switch_tail1, switch_state};

    b.setUpBlock(line, num, temp_sw, crossing_id);
    blocks.push_back(b);
}

void TrackController::setSignalsInstance(CTCSignals &s){

   // route = s.getRoute( (region - 1), line);
    //ctc_exit_id = s.getWaysideExit(wayside_id);
    //ctc_exit_id = 10;


 if (!initialized_ctcstruct) {

     ctc_wayside = s;

    if (line == "Green Line") {
       for (auto k = blocks.begin(); k != blocks.end(); k++) {
            for (int n = 0; n < 150; n++) {
                if ( (ctc_wayside.greenblockptr[n].block_id) == (k -> block_num) ) {
                    ctc_wayside.greenblockptr[n].wayside_id = wayside_id;
                }
            }
       }
    }

    if (line == "Red Line") {
        for (auto k = blocks.begin(); k != blocks.end(); k++) {
             for (int n = 0; n < 76; n++) {
                 if ( (ctc_wayside.redblockptr[n].block_id) == (k -> block_num) ) {
                     ctc_wayside.redblockptr[n].wayside_id = wayside_id;
                 }
             }
        }
    }

    initialized_ctcstruct = true;
  }

   std::vector<std::pair<int, int> > temp = s.getWaysideAuth(wayside_id, cntrl_blocks);


   std::vector<std::pair<int, int> > new_auth, first_auth, second_auth;

   std::vector<float> first_spd, second_spd, new_speed;

   int first_exit = ctc_exit_id;
   int second_exit = s.getWaysideExit(wayside_id);
   float spd = s.getWaysideSpeed(wayside_id);

   bool train_ahead = false;



   if ( (temp.begin() -> first) == -1 ) {
       for (int m = 0; m < block_count; m++) {
           CTC_sugauth.push_back(std::make_pair(cntrl_blocks[m], 0));

       }
       CTC_sugspeed = spd;
   }
   else {
       if (!CTC_sugauth.empty()) {

           for (auto y = CTC_sugauth.rbegin(); y != CTC_sugauth.rend(); y++) {
               first_auth.push_back(*y);
           }

           for (auto y = temp.rbegin(); y != temp.rend(); y++) {
               second_auth.push_back(*y);
           }




           if ( (temp.begin() -> first) == -1 ) {
               for (int m = 0; m < block_count; m++) {
                   CTC_sugauth.push_back(std::make_pair(cntrl_blocks[m], 0));
               }
           }

           CTC_sugspeed = spd;
           for (int m = 0; m < block_count; m++) {
               for ( auto a = occ_vect.begin(); a != occ_vect.end(); a++) {
                   a++;
                   if (cntrl_blocks[m+1] == a -> first) {
                       train_ahead = a -> second;

                       if (!train_ahead) {
                           new_auth.push_back(second_auth.back());
                           second_auth.pop_back();
                           first_auth.pop_back();


                       }
                       else {
                           while (!first_auth.empty()) {
                            new_auth.push_back(first_auth.back());
                            first_auth.pop_back();


                           }
                           break;
                       }

                       if (train_ahead) {
                           break;
                       }
                   }
                   a--;


               }

               if (train_ahead) {
                   break;
               }
           }

       }

  else {
       for (auto i = temp.begin(); i != temp.end(); i++) {
           CTC_sugauth.push_back(*i);
       }

       for (int m = 0; m < block_count; m++) {
           bool found = false;
           auto a = CTC_sugauth.begin();
           auto end = CTC_sugauth.end();

           while (!found) {
               if ( (a ->first) == cntrl_blocks[m] ) {
                   found = true;
                   a++;
               }
               else {
                   a++;
                   if (a == end) {
                       CTC_sugauth.push_back(std::make_pair(cntrl_blocks[m], 0));
                       found = true;
                   }
               }

           }

       }

       float spd = s.getWaysideSpeed(wayside_id);
       CTC_sugspeed = spd;

}

   if ( second_exit != -1) {
       if (train_ahead) {
        ctc_exit_id = first_exit;
        hold_exit = true;
       }
       else {
           ctc_exit_id = second_exit;
           hold_exit = false;
       }
   }


}
   setTrackSA();

}

/*int TrackController::getResult() {
	std::cout << "region: " << region << "\n\n";
	std::cout << "sections: ";
	for ( auto i = cntrl_sections.begin(); i != cntrl_sections.end(); ++i) 
        std::cout << *i << " ";
    std::cout << "\n\nblocks: ";
    for ( auto i = cntrl_blocks.begin(); i != cntrl_blocks.end(); ++i) 
        std::cout << *i << " ";
    std::cout << "\n\nswitches: ";
    for ( auto i = cntrl_switches.begin(); i != cntrl_switches.end(); ++i) 
        std::cout << *i << " ";
        
    return 0;
}*/

void TrackController::setRoute() {
 /*  route = ctc_wayside.getRoute(region, line);
    if (switch_head != -1) {
        if ( !PLC.checkRoute(route) ) {
            setSwitch(!route);
        }
        else {
            setSwitch(route);
        }
    }
    else {
        if ( !PLC.checkRoute(route) ) {
            route = !route;
        }
    }
*/
    //ADD FUNCTION CALL TO TRACKLOGIC TO SET SWITCH STATE BASED ON bool route OF TrackController CLASS
}

void TrackController::setSwitch(bool state) {

    if (switch_head != -1) {
        switch_state = state;

    bool relay_change = PLC.setSwitch(switch_state);
    TrackModel::SwitchState s;
    if (relay_change == true) {
        if (switch_state == 0) {
            blocks[switch_tail0-1].active_tail = true;
            blocks[switch_tail1-1].active_tail = false;
            s = TrackModel::SwitchState::SW_STRAIGHT;
        }
        else {
            blocks[switch_tail0-1].active_tail = false;
            blocks[switch_tail1-1].active_tail = true;
            s = TrackModel::SwitchState::SW_DIVERGING;
        }
    }
    else {
        if (switch_state == 0) {
            blocks[switch_tail0-1].active_tail = true;
            blocks[switch_tail1-1].active_tail = false;
            s = TrackModel::getSwitchState(line, switch_head);
            if (s != TrackModel::SwitchState::SW_STRAIGHT) {
                s = TrackModel::SwitchState::SW_STRAIGHT;
            }
        }
        else {
            blocks[switch_tail0-1].active_tail = false;
            blocks[switch_tail1-1].active_tail = true;
            s = TrackModel::SwitchState::SW_DIVERGING;
            if (s != TrackModel::SwitchState::SW_DIVERGING) {
                s = TrackModel::SwitchState::SW_DIVERGING;
            }
        }
    }
        TrackModel::setSwitchState(line, switch_head, s);
    }
}

void TrackController::setSwitchAuto() {

    if (switch_head != -1) {
        bool temp_occ_h = false;
        bool temp_occ_0 = false;
        bool temp_occ_1 = false;

        for (auto c = occ_vect.begin(); c != occ_vect.end(); c++) {
            if (c -> first == switch_head) {
                temp_occ_h = c -> second;
            }
            if (c -> first == switch_tail0) {
                temp_occ_0 = c -> second;
            }
            if (c -> first == switch_tail1) {
                temp_occ_1 = c -> second;
            }
        }
    TrackModel::SwitchState s = TrackModel::SwitchState::SW_STRAIGHT;
    if (temp_occ_h) {
        if (ctc_exit_id == exit_block0) {
            //blocks[switch_tail0-1].active_tail = true;
            //blocks[switch_tail1-1].active_tail = false;
            s = TrackModel::SwitchState::SW_STRAIGHT;
        }
        else {
            if (exit_block0 == 88) {
                s = TrackModel::SwitchState::SW_STRAIGHT;
            }
            else {
            s = TrackModel::SwitchState::SW_DIVERGING; }
        }
    }
    else {
        if (temp_occ_0) {

            if (ctc_exit_id == start_block) {
                s = TrackModel::SwitchState::SW_STRAIGHT;
            }
        }
        else if (temp_occ_1) {

            if (ctc_exit_id == start_block) {
                s = TrackModel::SwitchState::SW_DIVERGING;
            }
        }
    }
        TrackModel::setSwitchState(line, switch_head, s);
    }
}

void TrackController::setCross() {

    if (crossing_id != -1) {
        //bool be_set = PLC.activateCrossing(blocks[crossing_id-1].block_occ);
    bool temp_occ = false;

    for (auto c = occ_vect.begin(); c != occ_vect.end(); c++) {
        if (c -> first == crossing_id) {
            temp_occ = c -> second;
            break;
        }
    }

       if (temp_occ) {
            cross_state = true;
            blocks[crossing_id - 1].cross_state = true;
            TrackModel::setCrossing(line, crossing_id, cross_state);
        }
        else {
            cross_state = false;
            blocks[crossing_id - 1].cross_state = false;
            TrackModel::setCrossing(line, crossing_id, cross_state);
        }
    }


}
void TrackController::manSetCross(bool state) {
    if (crossing_id != -1) {
        cross_state = state;
        blocks[crossing_id - 1].cross_state = state;
        TrackModel::setCrossing(line, crossing_id, cross_state);
    }
}

void TrackController::getFaults() {

    std::vector<std::pair<int, int> > temp;

    TrackModel::BlockFault fault;
    int fault_num;
    for ( int i = 0; i < block_count; i++) {
        fault = TrackModel::getFaults(line, cntrl_blocks[i]);
        if (fault == TrackModel::BlockFault::FAULT_NONE) {
            fault_num = 0;
        }
        else if (fault == TrackModel::BlockFault::FAULT_BROKEN_RAIL) {
            fault_num = 1;
        }
        else if (fault == TrackModel::BlockFault::FAULT_CIRCUIT_FAIL) {
            fault_num = 2;
        }
        else  {
            fault_num = 4;
        }

        temp.push_back(std::make_pair(cntrl_blocks[i], fault_num));
    }

    faults_vect = temp;
}

void TrackController::getOccupancies() {

    std::vector<std::pair<int, bool> > temp;
    int block_occ;
    for ( int i = 0; i < block_count; i++) {
        block_occ = TrackModel::isBlockOccupied(line, cntrl_blocks[i]);
        temp.push_back(std::make_pair(cntrl_blocks[i], block_occ));
    }

    occ_vect = temp;

}

void TrackController::setTrackSA() {

   // int c = 0;
    int curr_block;

    int tempID;
    std::vector<std::pair< int, int> > temp_ctcA;

    for ( int i = 0; i < block_count; i++) {
        //c = 0;
        curr_block = cntrl_blocks[i];


        for (auto m = CTC_sugauth.begin(); m != CTC_sugauth.end(); m++) {
            tempID = m -> first;

            if ( curr_block == tempID ) {

                TrackModel::TrackCircuitData circ_data = TrackModel::TrackCircuitData::fromFloat(CTC_sugspeed, m -> second);
                TrackModel::setTrackCircuit(line, tempID, circ_data);
                //m = CTC_sugauth.end();
            }

        }
    }

    if (switch_head != -1) {

        if (ctc_exit_id == exit_block0) {
            setSwitch(true);
        }
        else {
            setSwitch(false);
        }
    }

}

void TrackController::updateData() {


    getOccupancies();
    getFaults();

    //struct BlockInfoCTC block_struct;

    for (auto b = blocks.begin(); b != blocks.end(); b++) {
        ctc_wayside.updateBlockOcc(line, occ_vect);
        ctc_wayside.updateBlockFail(line, faults_vect);
       }

/*
    std::vector<std::pair<int, int> > temp = ctc_wayside.getWaysideAuth(wayside_id, cntrl_blocks);

    for (auto i = temp.begin(); i < temp.end(); i++) {
        CTC_sugauth.push_back(*i);
    }

    float spd = ctc_wayside.getWaysideSpeed(wayside_id);

    for (int m = 0; m < block_count; m++) {
        CTC_sugspeed.push_back(spd);
    }

    ctc_exit_id = ctc_wayside.getWaysideExit(wayside_id);
    */

    setCross();
    setSwitchAuto();
    //setTrackSA();
}
