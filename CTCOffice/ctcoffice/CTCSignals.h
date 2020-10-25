//ADD GUARD
#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

#include <iostream>
#include <vector>


class CTCSignals {
private:
    void setFlag(bool);

public:
    bool update_flag;
    float speedCTC;
    float authCTC;
    int destinationBlock;

    void setSignal(int b, float s, float a);
    int getDest();
    float getSpeed();
    float getAuth();
};

//END GUARD
#endif
