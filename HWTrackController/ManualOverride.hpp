#ifndef MANUALOVERRIDE_H
#define MANUALOVERRIDE_H

class ManualOverride
{
private:
	bool manualSwitch;
	bool switchingSwitch;
	bool crossingSwitch;
	bool stopRequest;
public:
	ManualOverride();
	
	// void updateLights(int); might go in block class
	
	void setManual(bool); 
	void setCrossing(bool);
	void setSwitch(bool);	
};

#endif