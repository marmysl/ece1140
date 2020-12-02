#include "waysidecontainer.h"



WaysideContainer::WaysideContainer()
{

}


void WaysideContainer::addTrackObj(int id, std::string &line, std::vector<char> &s, std::vector<int> &b) {
    using namespace std;
    TrackController t;
    t.setUpController(id, line, s, b);
    waysides.push_back(t);

    for(auto i = b.begin(); i != b.end(); i++){
        t.addBlockObj(*i);
    }


}

/*void WaysideContainer::addBlockObj(int num) {
    using namespace std;
    BlockCntrl b;
    b.setUpBlock(num);
    blocks.push_back(b);
}*/

void WaysideContainer::addCTCObj(CTCSignals &) {

    CTCSignals wayside_signals = ctc_track_controller;

        waysides.begin() -> setSignalsInstance(wayside_signals);

}
