#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

class CTCSignals
{
public:
	void setSpeedAuth(float[], float[]), int;
	std::vector<float> speedCTC;
	std::vector<float> authCTC; 
	std::vector<float> getSpeed();
	std::vector<float> getAuth();
	int destinationBlock;
};

#endif
