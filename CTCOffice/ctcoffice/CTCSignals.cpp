#include <iostream>
#include "CTCSignals.h"
#include <vector>


void CTCSignals::setFlag(bool flag) {
        update_flag = flag;
}

void CTCSignals::setSignal(int b, std::vector<float> &s, std::vector<float> &a) {
        destinationBlock = b;
        for(int i = 0; i < s.size(); i++) {
            speedCTC.push_back(s[i]);
            authCTC.push_back(a[i]);
        }
}

std::vector<float> CTCSignals::getSpeed() {
    return speedCTC;
}

std::vector<float> CTCSignals::getAuth() {
    return authCTC;
}

int CTCSignals::getDest() {
    return destinationBlock;
}
