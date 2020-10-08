#ifndef MANUALOVERRIDE_H
#define MANUALOVERRIDE_H

#include "Region.hpp"

class ManualOverride
{
private:
	int blockNum;
	bool manualSwitch;
	bool switchingSwitch;
	bool crossingSwitch;
	bool stopRequest;
public:
	ManualOverride(Region &);
	void setManual(bool); 
	void setCrossing(bool);
	void setSwitch(bool);	
};

#endif