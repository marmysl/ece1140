#include <iostream>
#include <iomanip>
#include <cstdint>
#include "ManualOverride.hpp"
using namespace std;

// Constructor
ManualOverride :: ManualOverride(Region &r) {
	route = r.getRoute();
	blockNum = r.getCurrentBlock();
	authority = r.getAuthority();
}

void ManualOverride :: setManual(bool b) {
	manualSwitch = b;
}

void ManualOverride :: setCrossing(bool b) {
	crossingSwitch = b;
}

void ManualOverride :: setSwitch(bool b) {
	switchingSwitch = b;
	//TrackModel::setSwitchState("Blue Line", blockNum, TrackModel::SwitchState b);
}

void ManualOverride :: getSwitch(bool b) {
	switchingSwitch = b;
}

bool ManualOverride :: getManual() {
	return manualSwitch;
}

bool ManualOverride :: getSwitches(bool b) {
	return switchingSwitch;
}

bool ManualOverride :: getcrossing(bool b) {
	return crossingSwitch;
}
