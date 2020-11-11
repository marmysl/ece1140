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
    bool cabinLights = 1;
    bool headlightsOn = 0;
    bool advertisementsOn = 0;
    bool announcementsOn = 0;
    string announcements = "";
    bool acOn = 0;
    bool heaterOn = 0;
    int temp = 72;

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
    void setTemp(int);
    int getTemp();
};

#endif // TRAINMODELCONTROLS_H
