#include <iostream>
#include <iomanip>
#include <cstdint>
#include <QString>
#include "Region.hpp"

using namespace std;

/* CONSTRUCTOR */
//---------------------------------------------------------------------------------
Region::Region(std::string line) {
    // Block Struct set up
    iterator = 0;
    region = 1;
    route = line;
    std::vector<std::string> sec;
    std::vector<int>  blc;
    std::vector<bool> sw;
    std::vector<bool> rc;

    if (line == "Green Line") {
        // stored track layout
        std::vector<std::string> greensec{"Y","J","J","J","K","K","K","K","K","K","L","L","L","L","L","M"};
        std::vector<int> greenb{0,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74};
        std::vector<bool> greensw{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0};
        std::vector<bool> greenrc{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

        // assignment operator
        sec = greensec;
        blc = greenb;
        sw = greensw;
        rc = greenrc;

   } else { // Red Line
        // stored track layout
        std::vector<std::string> redsec{"A","A","A","B","B","B","C","C","C","D","D","D"};
        std::vector<int> redb{0,63,64,65,66,67,68,69,70,71,72,73};
        std::vector<bool> redsw{0,0,0,0,0,0,0,0,0,0,0,0};
        std::vector<bool> redrc{0,0,0,0,0,0,0,0,0,0,0,0};

        // assignment operator
        sec = redsec;
        blc = redb;
        sw = redsw;
        rc = redrc;
    }

   // assign to block structure
   for (size_t i = 0; i < blc.size(); i++ ){
        BlockInfo b;
        b.section = sec[i];
        b.blockID = blc[i];
        b.isSwitch = sw[i];
        b.isCrossing = rc[i];
        b.lightColor[0] = {1};        // Array initialized to [1,0] which is green
        b.lightColor[1] = {0};
        b.sugSpeed = 0.0;
        b.commSpeed = 0.0;
        b.auth = 0.0;
        b.switchActivated = 0;        // if there is no switch at the block, this value is ignored
        b.crossingActivated = 0;      // if there is no crossing at the block, this value is ignored
        b.occupancy = 0;
        b.failure = 0;

        blocks.push_back(b);          // block structures sent to vector of all blocks
   }
}

/* PLC METHODS */
//---------------------------------------------------------------------------------
// Load the PLC file and parse it
bool Region::loadPLC(QString filename) {
    success = plc->interpretHWPLC(filename);
    automatic = 1;
    return success;
}

void Region::runPLC() {
    if (automatic == 1) {

        std::vector<std::string> conds = plc->getConditions();
        std::vector<std::string> opts = plc->getOutputs();
        std::vector<int> blcs = plc->getBlocks();
        std::vector<int> opbcs = plc->getOutputBlocks();
        bool color[2];

        // Iterate through condition blocks
        for (unsigned int i = 0; i < blcs.size(); i++) {
            // not occupied block
            if (conds[i].at(0) == '!' && conds[i].at(1) == 'b') {
                if (detectTrain(blcs[i], getRoute()) == 0) {
                    // AUTO SWITCHES
                    if (opts[i].at(0) == 's') {
                        // switch should be activated (diverging)
                        TrackModel::setSwitchState(route,opbcs[i],static_cast<TrackModel::SwitchState>(1));
                    } else if (opts[i].at(0) == '!' && opts[i].at(1) == 's') {
                        // switch should be at default (normal)
                        TrackModel::setSwitchState(route,opbcs[i],static_cast<TrackModel::SwitchState>(0));
                    }
                    // AUTO LIGHTS BASED ON BLOCk
                    if (opts[i].at(0) == 'g') {
                        color[0] = 1;
                        color[1] = 0;
                        setLights(opbcs[i],route,color);
                    } else if (opts[i].at(0) == 'r') {
                        color[0] = 0;
                        color[1] = 0;
                        setLights(opbcs[i],route,color);
                    } else if  (opts[i].at(0) == 'y') {
                        color[0] = 0;
                        color[1] = 1;
                        setLights(opbcs[i],route,color);
                    }
                }
            // occupied block
            } else if (conds[i].at(0) == 'b') {
                if (detectTrain(blcs[i], getRoute()) == 1) {
                    if (opts[i].at(0) == 's') {
                        // switch should be activated (diverging)
                        TrackModel::setSwitchState(route,opbcs[i],static_cast<TrackModel::SwitchState>(1));
                    } else if (opts[i].at(0) == '!' && opts[i].at(1) == 's'){
                        // switch should be at default (normal)
                        TrackModel::setSwitchState(route,opbcs[i],static_cast<TrackModel::SwitchState>(0));
                    }
                    //AUTO LIGHTS BASED ON BLOCK
                    if (opts[i].at(0) == 'g') {
                        color[0] = 1;
                        color[1] = 0;
                        setLights(opbcs[i],route,color);
                    } else if (opts[i].at(0) == 'r') {
                        color[0] = 0;
                        color[1] = 0;
                        setLights(opbcs[i],route,color);
                    } else if  (opts[i].at(0) == 'y') {
                        color[0] = 0;
                        color[1] = 1;
                        setLights(opbcs[i],route,color);
                    }
                }
            // AUTO LIGHTS BASED ON SWITCHES
            } else if (conds[i].at(0) == '!' && conds[i].at(1) == 's') {
                if (TrackModel::getSwitchState(route,blcs[i]) == 0) {
                     if (opts[i].at(0) == 'r') {
                         color[0] = 0;
                         color[1] = 0;
                         setLights(opbcs[i],route,color);
                     } else if (opts[i].at(0) == 'g'){
                         color[0] = 1;
                         color[1] = 0;
                         setLights(opbcs[i],route,color);
                     } else if  (opts[i].at(0) == 'y') {
                         color[0] = 0;
                         color[1] = 1;
                         setLights(opbcs[i],route,color);
                     }
                }
            } else if (conds[i].at(0) == 's') {
                if (TrackModel::getSwitchState(route,blcs[i]) == 1) {
                     if (opts[i].at(0) == 'r') {
                         color[0] = 0;
                         color[1] = 0;
                         setLights(opbcs[i],route,color);
                     } else if (opts[i].at(0) == 'g'){
                         color[0] = 1;
                         color[1] = 0;
                         setLights(opbcs[i],route,color);
                     } else if  (opts[i].at(0) == 'y') {
                         color[0] = 0;
                         color[1] = 1;
                         setLights(opbcs[i],route,color);
                     }
                }
            }
        }
    }
}

/* CTC METHODS */
//---------------------------------------------------------------------------------
// Initialize speed and authority allowed in the region
void Region :: initialize(int db, float ss, std::vector<std::pair<int,int>> ac) {

    // assign speed, authority, and exit block
    exitBlock = db;

   for (unsigned int j = 0; j < blocks.size(); j++) {
        for (unsigned int i = 0; i < ac.size(); i++) {
            if (blocks[j].blockID == ac[i].first) {
                blocks[j].sugSpeed = ss;
                blocks[j].commSpeed = ss;
                blocks[j].auth = ac[i].second;
            }
        }
    }

    // relay information to Track Model
    setCircuit();
}

// Pick up track occupancy of block on desired line
bool Region :: detectTrain(int b, string line) {
    int loc;

    if (line == "Green Line") {
        if (b == 0) { loc = 0; }
        else { loc = b - 59; } // Track Controller specific solution
    }

    if (line == "Red Line") {
        loc = 0;
    }

    blocks[loc].occupancy = TrackModel::isBlockOccupied(line, b);
    return blocks[loc].occupancy;
}

/* TRACK MODEL METHODS */
//---------------------------------------------------------------------------------
// Retrieve Speed Limit
float Region::getSpeedLimit() const{
    // check that current block is equal to the input block (that could be included in the arguments)?
    TrackModel::Block *currentBlock;
    float speedLimit = currentBlock->speedLimit;
    return speedLimit;
}

// Set Track Circuit
void Region :: setCircuit() {
    for (unsigned int i = 0; i < blocks.size(); i++){
        TrackModel::TrackCircuitData tcdata = TrackModel::TrackCircuitData::fromFloat(blocks[i].commSpeed,blocks[i].auth);
        std::cout << "Setting Track Circuit: Block " << blocks[i].blockID << ", Speed set to " <<  blocks[i].commSpeed << ", Authority set to " << blocks[i].auth << std::endl;
        TrackModel::setTrackCircuit(route, blocks[i].blockID, tcdata);
}}

// Get Failures
bool Region :: detectFailure(int b, string line) {
    int val = TrackModel::getFaults(line, b);
    int loc;

    if (line == "Green Line") {
        if (b == 0) { loc = 0; }
        else { loc = b - 59; } // Track Controller specific solution
    }
    if (line == "Red Line") { loc = 0; }

    if (val != 0) { blocks[loc].failure = 1; }
    return blocks[loc].failure;
}

// Set Traffic Lights
void Region :: setLights(int b, string line, bool color[]) {
    int loc;

    if (line == "Green Line") {
        if (b == 0) { loc = 0; }
        else { loc = b - 59; } // Track Controller (region) specific solution
    }
    if (line == "Red Line") { loc = 0; }

    blocks[loc].lightColor[0] = color[0];
    blocks[loc].lightColor[1] = color[1];

    // conversion for track model
    if (color[0] == 0 && color[1] == 0)  {
        TrackModel::setSignal(line,b,static_cast<TrackModel::BlockDir>(1),static_cast<TrackModel::SignalState>(0));
        TrackModel::setSignal(line,b,static_cast<TrackModel::BlockDir>(-1),static_cast<TrackModel::SignalState>(0));
    } else if (color[0] == 0 && color[1] == 1) {
        TrackModel::setSignal(line,b,static_cast<TrackModel::BlockDir>(1),static_cast<TrackModel::SignalState>(1));
         TrackModel::setSignal(line,b,static_cast<TrackModel::BlockDir>(-1),static_cast<TrackModel::SignalState>(1));
    } else if (color[0] == 1 && color[1] == 0) {
        TrackModel::setSignal(line,b,static_cast<TrackModel::BlockDir>(1),static_cast<TrackModel::SignalState>(2));
         TrackModel::setSignal(line,b,static_cast<TrackModel::BlockDir>(-1),static_cast<TrackModel::SignalState>(2));
    }

};

/* GETTERS AND MISCELLANEOUS INTERNAL METHODS */
//---------------------------------------------------------------------------------
//void Region::timerEvent(QTimerEvent *event) {
//    if (success == 1) {
//        runPLC();
//    }
//}

std::string Region::getRoute() const {  // Line 
    return route;
}

std::string Region::getSection(int b) const { // Section
    if (b != 0) {
        b-= 59;
    }
    return blocks[b].section;
}

int Region::getCurrentBlock() const { // Current Block
    if (iterator != 0) {
        return (iterator + 59);
    } else {
         return iterator;
    }
}

float Region::getSuggestedSpeed(int b) const{ // Suggested Speed
    if (b != 0) {
        b-= 59;
    }
    return blocks[b].sugSpeed;
}

float Region::getCommandedSpeed(int b) const { // Commanded Speed
    if (b != 0) {
        b-= 59;
    }
    return blocks[b].commSpeed;
}

float Region::getAuthority(int b) const{ // Authority
    if (b != 0) {
        b-= 59;
    }
    return blocks[b].auth;
}

int Region::getLights(int b) const{ // Authority
    int color;
    if (b != 0) {
        b-= 59;
    }
    if (blocks[b].lightColor[0] == 0 && blocks[b].lightColor[0] == 0) {
        color = 0;
    } else if (blocks[b].lightColor[0] == 0 && blocks[b].lightColor[0] == 1) {
        color = 1;
    } else {
        color = 2;
    }
    return color;
}

void Region::setCurrentBlock(int b){
    if (b != 0) {
        iterator = b - 59;
    } else {
        iterator = 0;
    }
}

int Region::getSwitchBlock() {
    for (unsigned int i = 0; i < blocks.size(); i++) {
        if (blocks[i].isSwitch == 1) {
            return blocks[i].blockID;
        }
    }
}

int Region::getCrossingBlock() {
    for (unsigned int i = 0; i < blocks.size(); i++) {
        if (blocks[i].isCrossing == 1) {
            return blocks[i].blockID;
        }
    }
    return 19; // for the purposes of demonstrating functionality in Green Line, in this region there is no railway crossing.
}
