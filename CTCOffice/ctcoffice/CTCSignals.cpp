#include <iostream>
#include "CTCSignals.h"
#include <vector>


void CTCSignals::setFlag(bool flag) {
        update_flag = flag;
}

void CTCSignals::setSignal(int b, float s, float a) {
        destinationBlock = b;
        speedCTC = s;
        authCTC = a;
}

float CTCSignals::getSpeed() {
    return speedCTC;
}

float CTCSignals::getAuth() {
    return authCTC;
}

int CTCSignals::getDest() {
    return destinationBlock;
}

void CTCSignals::setUp(int id) {
    receiving_wayside = id;

}

