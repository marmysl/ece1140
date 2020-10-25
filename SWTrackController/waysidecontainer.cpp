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

}

void WaysideContainer::addBlockObj(int num) {
    using namespace std;
    BlockCntrl b;
    b.setUpBlock(num);
    blocks.push_back(b);
}
