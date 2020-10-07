#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Track.hpp"

using namespace std;

// Constructor
Track :: Track() {
	route = getRoute();
	blockNum = getCurrentBlock();
	authority = getAuthority();
	blockOccupancy = 0;
	lights = 0;
}

void Track :: viewTrack() {
	// returns parsed file to serial monitor
	// show Track Controller the configuration of the track
}

bool Track :: detectTrain() {
	blockOccupancy = TrackModel::isBlockOccupied(route, blockNum);

	cout << " train detected is " << blockOccupancy; 

	return blockOccupancy;
}

void Track :: updateTrack() {

}


void Track :: updateLights() {
	// Control traffic lights based on authority (speed must slow down accordingly)
	if (authority > 30) {
		lights = 0; // green
	} else if (authority < 30 && authority > 15) {
		lights = 1; //yellow
	} else if (authority < 15) {
		lights = 2; // red
	}

	cout << "lights are " << lights << endl;
}

int Track :: switchState() {

	switchpath = 6;
    //switchpath = TrackModel::getSwitchState(route, 5);
    cout << " Switch is pointed to " << switchpath; 
    return switchpath;
}