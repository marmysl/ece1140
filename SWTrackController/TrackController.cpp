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

    std::vector<float> ctc_speed_temp;
    ctc_speed_temp = s.getSpeed(region, line);

    std::vector<int> ctc_auth_temp;
    ctc_auth_temp = s.getAuth(region, line);

    int c = 0;
    for ( auto i = blocks.begin(); i != blocks.end(); i++) {
        i -> setSpdAuth(ctc_auth_temp[c], ctc_auth_temp[c]);
        c++;
    }


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
//ADD FUNCTION CALL TO TRACKLOGIC TO SET SWITCH STATE BASED ON bool route OF TrackController CLASS
}

void TrackController::setSwitch(bool state) {
    switch_state = state;
}
