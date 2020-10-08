#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

class CTCSignals
{
public:
	void setSignal(int, float[], float[]);
	std::vector<float> speedCTC;
	std::vector<float> authCTC; 
	int destinationBlock;
	std::vector<float> getSpeed();
	std::vector<float> getAuth();
	int getDest();
};

#endif