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
    int receiving_wayside;

    void setSignal(int, float, float);
    int getDest();
    float getSpeed();
    float getAuth();
    void setUp(int);

};

//END GUARD
#endif
