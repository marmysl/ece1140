#include <iostream>
#include "CTCSignals.h"
#include <vector>


void CTCSignals::setFlag(bool flag) {
        update_flag = flag;
}

void CTCSignals::setSignal(int r, float s, int a) {

        speedCTC = s;
        authCTC = a;
}

float CTCSignals::getSpeed() {
    return speedCTC;
}

float CTCSignals::getAuth() {
    return authCTC;
}



