#ifndef TRACKLAYOUT_H
#define TRACKLAYOUT_H

#include <string>
#include "Region.hpp"

class Track : private Region
{
private:
	std::string route;
	int blockNum;
	float authority;
	double speedLimit;
	bool blockOccupancy = 0;
	int lights;
	int switchpath; 

public:
	Track();
	void viewTrack();
	bool detectTrain();
	void updateTrack();
	void updateLights();
	int switchState(); 

};

#endif //TRACKLAYOUT_H