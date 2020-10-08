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
    std::vector<float> speedCTC;
    std::vector<float> authCTC;
    int destinationBlock;

    void setSignal(int b, std::vector<float> &s, std::vector<float> &a);
    int getDest();
    std::vector<float> getSpeed();
    std::vector<float> getAuth();
};

//END GUARD
#endif
