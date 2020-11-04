#include "waysidecontainer.h"

WaysideContainer::WaysideContainer()
{

}


void WaysideContainer::addTrackObj(int id, std::vector<char> &s, std::vector<int> &b) {
    using namespace std;
    TrackController t;
    t.setUpController(id, s, b);
    waysides.push_back(t);

    for(int i = 1; i <=15; i++){
        addBlockObj(i);
    }

    addCTCObj(id);
}

void WaysideContainer::addBlockObj(int num) {
    using namespace std;
    BlockCntrl b;
    b.setUpBlock(num);
    blocks.push_back(b);
}
void WaysideContainer::addCTCObj(int num) {
    using namespace std;
    CTCSignals c;
    c.setUp(num);
    sig.push_back(c);
}
