#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdint>

#include "HWTrackController.hpp"
#include "HWTrackController_main.h"

using namespace std;

int init_HWTrackController() {

    // Call the HW Track Controller
    HWTrackController();
    //sendtoRegion(HWTrackController->reg,ctcsig);

	// Instantiate objects for testing
    //	Region r1;
    //	CTCSignals c1;
    //	c1.setSignal(b, speeds, auths);
    //	cout << "speed in CTC signal class: ";
    //	for (auto it = c1.speedCTC.begin(); it != c1.speedCTC.end(); it++)
    //        cout << *it << " ";
    //    cout << c1.getDest() << endl;
    //    r1.initialize(c1);
    //    Track t1(r1);
    //    t1.detectTrain();
    //    t1.updateLights();
    // failures check
    // int yes = fd1.detectFailure();
    // cout << " Failure code is " << yes << endl;
    // track check
    // t1.switchState();

	return 0;
}

