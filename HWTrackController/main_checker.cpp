#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdint>

#include "Region.hpp"
#include "Region.cpp"
#include "CTCSignals.cpp"

// #include "FailureDetector.hpp"
// #include "FailureDetector.cpp"
// #include "PLC.hpp"
// #include "PLC.cpp"
// #include "ManualOverride.hpp"
// #include "ManualOverride.cpp"
// #include "Track.hpp"
// #include "Track.cpp" 

using namespace std;

int main() {
	// Instantiate objects for testing
	 Region r1;
	CTCSignals c1;
	
	float speeds[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	float auths[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	
	c1.setSpeedAuth(speeds,auths);

	cout << "speed in CTC signal class: ";
	for (auto it = c1.speedCTC.begin(); it != c1.speedCTC.end(); it++) 
        cout << *it << " "; 

    cout << endl;
    r1.initialize(c1);



	return 0;
}

