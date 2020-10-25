#include "waysidecontainer.h"
#include "tracklogic.h"
#include "CTCOffice/ctcoffice/CTCSignals.h"
#include <vector>

int init_SWTrackController() {
	
    CTCSignals C1;

    WaysideContainer wayside_vector;

    std::vector<char> s;
    s.push_back('A');
    s.push_back('B');
    s.push_back('C');

    std::vector<int> b;
    for(int i = 1; i <= 15; i++) {
        b.push_back(i);     }

    wayside_vector.addTrackObj(1, s, b);
	
    //timer implementation


    wayside_vector.blocks.begin() -> setSpdAuth(1, C1.speedCTC, C1.authCTC);


    for (auto i = wayside_vector.blocks.begin(); i != wayside_vector.blocks.end(); ++i) {
        i -> setOcc();    }


	return 0;
}

