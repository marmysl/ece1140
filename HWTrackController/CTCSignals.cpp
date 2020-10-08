#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include "CTCSignals.hpp"
using namespace std;

void CTCSignals :: setSignal(int b, float s[], float a[]) {
	for (int i = 0; i < 15; i++){
		speedCTC.push_back(s[i]);
	}
	for (int i = 0; i < 15; i++){
		authCTC.push_back(a[i]);
	}

	destinationBlock = b;
}

std::vector<float> CTCSignals :: getSpeed() {
	return speedCTC;
}

std::vector<float> CTCSignals :: getAuth() {
	return authCTC;
}

int CTCSignals :: getDest() {
	return destinationBlock;
}