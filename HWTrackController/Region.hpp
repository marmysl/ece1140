#ifndef REGION_H
#define REGION_H

// The Region class stores all the information about the block that you are currently in ( blocks can be switched through )
// That information is written and displayed on the Arduino LCD -> Section, Block, Commanded Speed, Authority
// This class also sends the track circuit information to the Track Signal

#include <QTimer>
#include <QObject>

#include <string>
#include <vector>
#include "HardwarePLC.h"
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
    int auth;                   // Authority
    bool switchActivated;       // Is the switch activated
    bool crossingActivated;     // Is the crossing (if in the block) activated
    bool occupancy;             // Is the block occupied
    bool failure;               // Is there a failure (broken rail)
};

class Region : public QObject
{
    Q_OBJECT

private:
    HardwarePLC *plc = new HardwarePLC();   // PLC Object
    int region;                             // Region # (always 1)
    std::string route;                      // Line
    int exitBlock;                          // Exit block for the region
    float suggestedSpeed;                   // Suggested Speed
    int suggestedAuth;                      // Suggested authority
    float speedLimit;                       // Block speed limit
    std::vector<BlockInfo> blocks;          // Vector of block structures containing block information
    int iterator;                           // Current Block for the UI, allows for displaying values on the lcd

public:
   // Wayside
    Region(std::string);
    bool success;
    bool loadPLC(QString);
    bool automatic;

    // CTC
    void initialize(int, float, std::vector<std::pair<int, int>>);
    bool detectTrain(int, std::string);

    // Track Model
    void setCircuit();
    float getSpeedLimit() const;
    bool detectFailure(int, std::string);
    void setLights(int, std::string, bool[2]);

    // Getters
    std::string getRoute() const;
    std::string getSection(int) const;
    int getCurrentBlock() const; 
    int getSwitchBlock();
    int getCrossingBlock();
    float getSuggestedSpeed(int) const;
    float getCommandedSpeed(int) const;
    float getAuthority(int) const;
    int getLights(int) const;

    // Other internal methods
    void setCurrentBlock(int);


public slots:
    void runPLC();
};

#endif
