//ADD GUARD
#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

#include <iostream>
#include <vector>


class CTCSignals {

public:

    float speedCTC;
    int authCTC;
    bool routeCTC;

    void setSignal(bool, float, int);
    bool getRoute(int);
    float getSpeed();
    int getAuth();

};

//END GUARD
#endif
