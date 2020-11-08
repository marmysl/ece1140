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
    bool r1;
    bool r2;

    void setSignal(int, float, float);
    bool getRoute(int);
    float getSpeed();
    float getAuth();

};

//END GUARD
#endif
