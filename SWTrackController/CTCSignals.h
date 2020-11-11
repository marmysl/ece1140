//ADD GUARD
#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

#include <iostream>
#include <vector>


class CTCSignals {

public:

    float speedCTC;
    int authCTC;
    int green_exit[12];
    int red_exit[10];
    int blue_exit[1];


    int setSignal(std::string &, int[], float, int);
    float getSpeed();
    int getAuth();
    int getExit(int, std::string &);


};

//END GUARD
#endif
