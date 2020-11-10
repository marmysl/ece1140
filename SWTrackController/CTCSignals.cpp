#include <iostream>
#include "CTCSignals.h"
#include <vector>


void CTCSignals::setSignal(bool r, float s, int a) {

        speedCTC = s;
        authCTC = a;
        routeCTC= r;
        std::cout << " This is set Signal SW Track Controller. This is the speed, authority and route from CTC.\n Speed: " << speedCTC << "\n Authority: " << authCTC << "\n Route: " << routeCTC << "\n";
}

float CTCSignals::getSpeed() {
    return speedCTC;
}

int CTCSignals::getAuth() {
    return authCTC;
}

bool CTCSignals::getRoute(int wayside_id) {
    return routeCTC;
}


