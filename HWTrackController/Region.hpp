#ifndef REGION_H
#define REGION_H
// The Region class stores all the information about the block that you are currently in ( all blocks can be switched through )
    // That information is written and displayed on the Arduino LCD -> Section, Block, Suggested Speed, Commanded Speed, Authority
    // This class also sends the track circuit information to the Track Signal

#include <string>
#include "CTCSignals.hpp"
#include "tracklayout.hpp"
#include "trackmodel_controller.hpp"
#include "trackmodel_test.hpp"

class Region
{
private: 
    int region;
    std::string route;
    std::vector<std::string> sections;
    std::string currentSection;
    std::vector<int> blocks;
    int currentBlock;
    int blockID;
    std::vector<float> suggestedSpeed;
    std::vector<float> commandedSpeed;
    std::vector<float> authority;
    std::vector<float> speedLimit;
public:
    // Constructor
    Region();
    // CTC initalize and check Speed Limit
    void initialize(CTCSignals &);
    // Getters and Setters
    std::string getRoute() const;
    std::string getSection() const;
    int getCurrentBlock() const;
    int getSuggestedSpeed() const;
    int getCommandedSpeed() const;
    int getAuthority() const;
    int getSpeedLimit() const;
    void setSection(std::string);
    void setCurrentBlock(int);
    void setCommandedSpeed(int, int);
    void setAuthority(int, int);
    void setCircuit(); 

    
};

#endif