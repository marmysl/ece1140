#ifndef REGION_H
#define REGION_H

// The Region class stores all the information about the block that you are currently in ( all blocks can be switched through )
// That information is written and displayed on the Arduino LCD -> Section, Block, Commanded Speed, Authority
// This class also sends the track circuit information to the Track Signal

#include <string>
#include <vector>

#include "../TrackModel/tracklayout.hpp"
#include "../TrackModel/trackmodel_controller.hpp"
#include "../TrackModel/trackmodel_main.hpp"

struct BlockInfo
{
    std::string section;        // Section
    int blockID;                // Block Number
    bool isSwitch;              // Is there a switch in the block
    bool isCrossing;            // Is there a railway crossing in the block
    bool lightColor[2];         // Color of the traffic lights
    float sugSpeed;             // Suggested Speed
    float commSpeed;            // Commanded Speed
    int auth;                 // Authority
    bool switchActivated;       // Is the switch activated
    bool crossingActivated;     // Is the crossing (if in the block) activated
    bool occupancy;             // Is the block occupied
};

class Region
{
private:
    int region;                             // Region # : 1
    std::string route;                      // Line
    int exitBlock;                          // exit block for the region, which will indicate the switch position
    float suggestedSpeed;                   // Suggested Speed value from CTC
    int suggestedAuth;                    // Suggested authority value from CTC
    float speedLimit;                       // Block speed limit picked up from Track Model
    std::vector<BlockInfo> blocks;          // Vector or block structures containing block information
    int iterator;                           // for the UI, displaying values on the lcd
public:
    Region();                               // Constructor

    Region(std::vector<std::string> sec,std::vector<int> blc, std::vector<bool> sw, std::vector<bool> rc); // constructor if the SWTC sends layout

    void initialize(int, float, std::vector<int>);     //  receive speed and authority from CTC using SWTC class
    void setCircuit();                      // Track Model: send speed and authority (track circuit information)t iteratorr;

    bool detectTrain(int, std::string);     // CTC: pick up block occupancy from Track Model
    float getSpeedLimit() const;            // Track Model: pick up speed limit for comparison

    //void setSwitch();                     // based on exit block, is the switch activated

    std::string getRoute() const;
    std::string getSection(int) const;
    int getCurrentBlock() const;
    float getSuggestedSpeed(int) const;
    float getCommandedSpeed(int) const;
    float getAuthority(int) const;

    // get lights
    // update lights

    void setCommandedSpeed(float, int);
    void setAuthority(float, int);

};

#endif
