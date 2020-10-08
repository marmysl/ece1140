#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdint>

#include "Region.hpp"
#include "Track.hpp"
#include "HWTrackController_main.h"

using namespace std;

int init_HWTrackController() {
	// Instantiate objects for testing
	
	Region r1;
	CTCSignals c1;
	
	// check CTC
    std::vector<float> speeds {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    std::vector<float> auths {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int b = 10;
	
	c1.setSignal(b, speeds, auths);

	cout << "speed in CTC signal class: ";
	for (auto it = c1.speedCTC.begin(); it != c1.speedCTC.end(); it++) 
        cout << *it << " "; 

    cout << c1.getDest() << endl;
    r1.initialize(c1);

    Track t1(r1);
    t1.detectTrain();
    t1.updateLights();


    // failures check
    // int yes = fd1.detectFailure();
    // cout << " Failure code is " << yes << endl;

    // track check
    
    
    // t1.switchState();

	return 0;
}

