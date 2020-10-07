#ifndef TRACKLAYOUT_H
#define TRACKLAYOUT_H

class TrackLayout
{
private:
	double speedLimit;
	bool blockOccupancy = 0;
public:
	TrackLayout();
	void viewTrack();
	void detectTrain(bool);
	void updateTrack();
};

#endif //TRACKLAYOUT_H