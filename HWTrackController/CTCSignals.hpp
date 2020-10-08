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

	void setSignal(int b, std::vector<float> &s, std::vector<float> &a) {
			destinationBlock = b;
			for(int i = 0; i < s.size(); i++) {
				speedCTC.push_back(s[i]);
				authCTC.push_back(a[i]);
			}
	}
	

    int getDest();
    std::vector<float> getSpeed();
    std::vector<float> getAuth();
};

#endif
