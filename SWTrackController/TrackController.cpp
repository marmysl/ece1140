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
    ctc_wayside = s;

    if (line == "Green Line") {
       for (auto k = blocks.begin(); k < blocks.end(); k++) {
            for (int n = 0; n < 150; n++) {
                if ( (ctc_wayside.greenblockptr[n].block_id) == (k -> block_num) ) {
                    ctc_wayside.greenblockptr[n].wayside_id = wayside_id;
                }
            }
       }
    }

    if (line == "Red Line") {
        for (auto k = blocks.begin(); k < blocks.end(); k++) {
             for (int n = 0; n < 76; n++) {
                 if ( (ctc_wayside.redblockptr[n].block_id) == (k -> block_num) ) {
                     ctc_wayside.redblockptr[n].wayside_id = wayside_id;
                 }
             }
        }
    }


    std::vector<std::pair<int, int> > temp = s.getWaysideAuth(wayside_id, cntrl_blocks);

    for (auto i = temp.begin(); i < temp.end(); i++) {
        CTC_sugauth.push_back(*i);
    }

    float spd = s.getWaysideSpeed(wayside_id);

    for (int m = 0; m < block_count; m++) {
        CTC_sugspeed.push_back(spd);
        //std::cout <<
    }

    ctc_exit_id = s.getWaysideExit(wayside_id);
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

void TrackController::setCross() {
   if (crossing_id != -1) {
        bool be_set = PLC.activateCrossing(blocks[crossing_id-1].block_occ);

        if (be_set) {
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

    TrackModel::BlockFault fault;
    for ( auto i = blocks.begin(); i != blocks.end(); i++) {
        fault = TrackModel::getFaults(line, i->block_num);
        int temp = fault;
        i -> block_fail = temp;
    }

}

void TrackController::setTrackSA() {

    int c = 0;
    int curr_block;

    int tempID;
    std::vector<std::pair< int, int> > temp_ctcA;

    for ( auto i = blocks.begin(); i != blocks.end(); i++) {
        c = 0;
        curr_block = i -> block_num;

        for (auto m = CTC_sugauth.begin(); m != CTC_sugauth.end(); m++) {
            tempID = m -> first;

            if ( curr_block == tempID ) {
                i -> setSpdAuth(CTC_sugspeed[c], m -> second);
                c++;
                TrackModel::TrackCircuitData circ_data = TrackModel::TrackCircuitData::fromFloat(CTC_sugspeed[c], m -> second);
                TrackModel::setTrackCircuit(line, tempID, circ_data);
            }
            else {
                c++;
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

    int c = 0;

    for (auto b = blocks.begin(); b < blocks.end(); b++) {
        b -> setOcc();
    }

    getFaults();

    for (auto b = blocks.begin(); b < blocks.end(); b++) {
        if (line == "Green Line") {
            while (c < 150) {
                ctc_wayside.greenblockptr[c].occupancy = (b -> block_occ);
                ctc_wayside.greenblockptr[c].failure_code = (b -> block_fail);
                c++;
            }
        }
        else if (line == "Red Line") {
            c = 0;
            while (c < 76) {
                ctc_wayside.redblockptr[c].occupancy = (b -> block_occ);
                ctc_wayside.redblockptr[c].failure_code = (b -> block_fail);
            }
        }
        else {
            c = 0;
            while (c < 15) {
                ctc_wayside.blueblockptr[c].occupancy = (b -> block_occ);
                ctc_wayside.blueblockptr[c].failure_code = (b -> block_fail);
            }
        }
    }

    std::vector<std::pair<int, int> > temp = ctc_wayside.getWaysideAuth(wayside_id, cntrl_blocks);

    for (auto i = temp.begin(); i < temp.end(); i++) {
        CTC_sugauth.push_back(*i);
    }

    float spd = ctc_wayside.getWaysideSpeed(wayside_id);

    for (int m = 0; m < block_count; m++) {
        CTC_sugspeed.push_back(spd);
    }

    ctc_exit_id = ctc_wayside.getWaysideExit(wayside_id);

    setCross();
    setTrackSA();
}
