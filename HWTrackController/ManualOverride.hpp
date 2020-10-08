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
    std::string route;
    int authority;

	ManualOverride(Region &);
	void setManual(bool); 
	void setCrossing(bool);
	void setSwitch(bool);	

    void getSwitch(bool b);
    bool getManual();
    bool getSwitches(bool b);
    bool getcrossing(bool b);
};

#endif
