#include <iostream>
#include "CTCSignals.h"
#include <vector>

void CTCSignals::setSignal(float s, int a, int r) {
    speedCTC = s;
    authCTC = a;
    routeCTC = r;
    std::cout << " This is set Signal HW Track Controller. This is the speed authority and route from the CTC: " << speedCTC << " " << authCTC << " " << routeCTC << std::endl;
}

float CTCSignals::getSpeed() {
    return speedCTC;
}

float CTCSignals::getAuth() {
    return authCTC;
}

int CTCSignals::getDestBlock(){
    return routeCTC;
}

//bool CTCSignals::getOccupancy(int blockNum){
//   return 0; // detectTrain(blockNum);
//}
