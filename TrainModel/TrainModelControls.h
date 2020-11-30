#ifndef TRAINMODELCONTROLS_H
#define TRAINMODELCONTROLS_H
#include <string>

using namespace std;

class TrainModelControls
{
public:
    bool doorOpen = 0;
    bool doorLeftOpen = 0;
    bool doorRightOpen = 0;
    bool cabinLights = 0;
    bool headlightsOn = 0;
    bool advertisementsOn = 0;
    bool announcementsOn = 0;
    string announcements = "";
    bool acOn = 0;
    bool heaterOn = 0;

    TrainModelControls();
    void toggleDoor(bool);
    void toggleLeftDoor(bool);
    void toggleRightDoor(bool);
    void toggleCabinLights(bool);
    void toggleHeadlights(bool);
    void toggleAdvertisments(bool);
    void toggleAnnouncements(bool);
    void setAnn(string);
    string getAnn();
    void toggleAC(bool);
    void toggleHeater(bool);
};

#endif // TRAINMODELCONTROLS_H
