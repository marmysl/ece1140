#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Track.hpp"

using namespace std;

// Constructor
Track :: Track(Region &r) {
	cout << " In Track class\n";
	route = r.getRoute();
	blockNum = r.getCurrentBlock();
	authority = r.getAuthority();
	blockOccupancy = 0;
	lights = 0;

	cout << route << endl;
	cout << blockNum << endl;
	cout << authority << endl;
	cout << blockOccupancy << endl;
	cout << lights << endl;

	// pickupSpeedLimit(r);
	// cout << speedLimit << endl;
}

void Track :: viewTrack() {
	// returns parsed file to serial monitor
	// show Track Controller the configuration of the track
}

bool Track :: detectTrain() {
	blockOccupancy = TrackModel::isBlockOccupied("Blue Line", blockNum);

	cout << " train detected is " << blockOccupancy << endl; 

	return blockOccupancy;
}

void Track :: updateTrack() {
}


void Track :: updateLights() {
	// Control traffic lights based on authority (speed must slow down accordingly)
	if (authority > 6) {
		lights = 0; // green
	} else if (authority < 6 && authority > 3) {
		lights = 1; //yellow
	} else if (authority < 3) {
		lights = 2; // red
	}

	cout << "lights are " << lights << endl;
}

int Track :: switchState() {

    // switchpath = TrackModel::getSwitchState("Blue Line", blockNum);
    // cout << " Switch is pointed to " << switchpath; 
    // return switchpath;
	return 0;
}

void Track :: pickupSpeedLimit(Region &r){
	// check that blocks match? 
	//TrackModel::Block *currentBlock;
	//float speedLimit = currentBlock -> speedLimit;

	speedLimit = 10;

	r.setSpeedLimit(blockNum, speedLimit);
}

int Track :: getLights() {
	return lights;
}