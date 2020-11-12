//This file contains the definitions of the member functions.
#include <iostream>
#include <vector>
#include "TrackController.h"
#include "waysidecontainer.h"

//using namespace std;

TrackController::TrackController(){


}

void TrackController::setUpController(int id, std::string &l, std::vector<char> &s, std::vector<int> &b, int sw[4], int cr, int fin[2]) {

    region = id;
    line = l;
    last_block[0] = fin[0];
    last_block[1] = fin[1];
    auto m = b.begin();
    start_block = *m;

    for (int i = 0; i < 4; i++) {
        switch_id[i] = sw[i];
    }
    crossing_id = cr;

    for (auto i = s.begin(); i != s.end(); i++) {
        cntrl_sections.push_back(*i);
    }
    for (auto i = b.begin(); i != b.end(); i++) {
        cntrl_blocks.push_back(*i);
        addBlockObj(*i);
    }

}

void TrackController::addBlockObj(int num) {
    using namespace std;
    BlockCntrl b;
    b.setUpBlock(line, num, switch_id, crossing_id, last_block[0], last_block[1]);
    blocks.push_back(b);
}

void TrackController::setSignalsInstance(CTCSignals &s){

    dest_block = s.getExit( (region - 1), line);

    setRoute();
    for ( auto i = blocks.begin(); i != blocks.end(); i++) {
        i -> setSpdAuth(s.speedCTC, s.authCTC);
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
