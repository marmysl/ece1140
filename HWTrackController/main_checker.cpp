#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdint>

#include "Region.hpp"
#include "Region.cpp"
#include "CTCSignals.cpp"
// #include "FailureDetector.cpp"
#include "Track.cpp"

// #include "PLC.hpp"
// #include "PLC.cpp"
// #include "ManualOverride.hpp"
// #include "ManualOverride.cpp"

using namespace std;

int main() {
	// Instantiate objects for testing
	
	Region r1;
	CTCSignals c1;
	
	// check CTC
	float speeds[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	float auths[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
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

