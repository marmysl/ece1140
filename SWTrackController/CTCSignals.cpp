#include <iostream>
#include "CTCSignals.h"
#include <vector>


int CTCSignals::setSignal(std::string &l, int r[], float s, int a) {
        if (l == "Green Line") {
            for(int i = 0; i < 12; i++) {
                green_exit[i] = r[i];
            }
        }
        else if (l == "Red Line") {
            for(int i = 0; i < 10; i++) {
                red_exit[i] = r[i];
            }
        }
        else if (l == "Blue Line") {
            for(int i = 0; i < 2; i++) {
                blue_exit[i] = r[i];
            }
        }
        else {
            return -1;
        }

        speedCTC = s;
        authCTC = a;

        return 0;
}

float CTCSignals::getSpeed() {
    return speedCTC;
}

int CTCSignals::getAuth() {
    return authCTC;
}

int  CTCSignals::getExit(int block, std::string &line) {
    int temp_exit;
    if (line == "Green Line") {
        temp_exit = green_exit[block-1];
    }
    else if (line == "Red Line") {
        temp_exit = red_exit[block-1];
    }
    else if (line  == "Blue Line") {
        temp_exit = blue_exit[block-1];
    }
    else {
        return -1;
    }
    return temp_exit;
}
