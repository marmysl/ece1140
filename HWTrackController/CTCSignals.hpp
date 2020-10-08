#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

#include <vector>
#include <iostream>

class CTCSignals
{
public:
	std::vector<float> speedCTC;
	std::vector<float> authCTC; 
	int destinationBlock;

        void setSignal(int b, std::vector<float> &s, std::vector<float> &a);
        int getDest();
};

#endif
