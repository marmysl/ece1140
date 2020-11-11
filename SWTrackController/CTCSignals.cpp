#include <iostream>
#include "CTCSignals.h"
#include <vector>


void CTCSignals::setFlag(bool flag) {
        update_flag = flag;
}

void CTCSignals::setSignal(int r, float s, int a) {
        exitBlock = r;
        speedCTC = s;
        authCTC = a;
}

float CTCSignals::getSpeed() {
    return speedCTC;
}

float CTCSignals::getAuth() {
    return authCTC;
}

int  CTCSignals::getExit() {
    return exitBlock;
}



