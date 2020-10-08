#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include "CTCSignals.hpp"
using namespace std;

std::vector<float> CTCSignals :: getSpeed() {
	return speedCTC;
}

std::vector<float> CTCSignals :: getAuth() {
	return authCTC;
}

int CTCSignals :: getDest() {
	return destinationBlock;
}