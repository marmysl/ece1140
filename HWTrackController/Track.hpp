#ifndef TRACK_H
#define TRACK_H

#include <string>
#include "Region.hpp"

class Track
{
private:
	std::string route;
	int blockNum;
	float authority;
	float speedLimit;
	bool blockOccupancy = 0;
	int lights;
	int switchpath; 

public:
	Track(Region &reg);
	void viewTrack();
	bool detectTrain();
	void updateTrack();
	void updateLights();
	int switchState(); 
	void pickupSpeedLimit(Region &reg);
	int getLights();

};

#endif //TRACH_H