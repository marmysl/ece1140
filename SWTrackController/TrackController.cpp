//This file contains the definitions of the member functions.
#include <iostream>
#include <vector>
#include "TrackController.h"
#include "waysidecontainer.h"

//using namespace std;

TrackController::TrackController(){
    block_count = 0;

}

void TrackController::setUpController(int id, std::string &l, std::vector<char> &s, std::vector<int> &b, int sw[], int cr) {

    region = id;
    line = l;

    switch_head = sw[0];
    switch_tail0 = sw[1];
    switch_tail1 = sw[2];
    switch_state = sw[3];

    if (cr == 0) {
        crossing_id = -1;
    }
    else {
        crossing_id = cr;
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

    route = s.getRoute( (region - 1), line);

    setRoute();

    //std::vector<float> ctc_speed_temp;
    CTC_sugspeed = s.getSpeed(region, line);

    //std::vector<int> ctc_auth_temp;
    CTC_sugauth = s.getAuth(region, line);

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
    route = ctc_wayside.getRoute(region, line);
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

    //ADD FUNCTION CALL TO TRACKLOGIC TO SET SWITCH STATE BASED ON bool route OF TrackController CLASS
}

void TrackController::setSwitch(bool state) {
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
    int c = block_count - 1;
    int y = 1;
    bool safe_s, safe_a;
    TrackModel::TrackCircuitData circ_data;
    CTC_tempauth = CTC_sugauth;
    CTC_tempspeed = CTC_sugspeed;

    for ( auto i = blocks.rbegin(); i != blocks.rend(); i++) {
        if ( (y) != block_count ) {
            i -> setSpdAuth(CTC_tempspeed[c], CTC_tempauth[c]);
            safe_s = PLC.checkSpeed(i -> plc_speed, blocks[c].block_occ);
            safe_a = PLC.checkAuth(i -> plc_auth, blocks[c].block_occ);
            if (safe_s && safe_a) {
                CTC_comauth[c] = CTC_tempauth[c];
                CTC_comspeed[c] = CTC_tempspeed[c];
            }
            else {
                if ( (i -> plc_auth) && (i -> plc_speed) ) {
                    CTC_comauth[c] = 0;
                    CTC_comspeed[c] = 0;
                    for (int m = c; m < 0; m--) {
                        CTC_tempauth[m-1] = CTC_tempauth[m];
                        CTC_tempspeed[m-1] = CTC_tempspeed[m];
                    }
                }
                else { //plc_auth && plc_speed = 0
                    CTC_comauth[c] = CTC_tempauth[c];
                    CTC_comspeed[c] = CTC_tempspeed[c];
                }
            }

        }
        c--;
        y++;
    i -> com_block_authority = CTC_comauth[c];
    i -> com_block_speed = CTC_comspeed[c];

    circ_data.fromFloat(CTC_comspeed[c], CTC_comauth[c]);
    TrackModel::setTrackCircuit(line, i -> block_num, circ_data);

    }

}

void TrackController::updateData() {
    getFaults();
    setCross();
    setTrackSA();
    setRoute();
}
