#ifndef MANUALOVERRIDE_H
#define MANUALOVERRIDE_H

class ManualOverride : private Region 
{
private:
	bool manualSwitch;
	bool switchingSwitch;
	bool crossingSwitch;
	bool stopRequest;
public:
	ManualOverride();
	void setManual(bool); 
	void setCrossing(bool);
	void setSwitch(bool);	
};

#endif