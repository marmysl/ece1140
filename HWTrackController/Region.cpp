#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Region.hpp"

using namespace std;

// Constructor
Region :: Region(std::string line) {

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
        std::vector<bool> greensw{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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
        b.lightColor[0] = {0};        // Array initialized to [0,0] which is green
        b.lightColor[1] = {0};
        b.sugSpeed = 0.0;
        b.commSpeed = 0.0;
        b.auth = 0.0;
        b.switchActivated = 0;        // if there is no switch at the block, this value is ignored
        b.crossingActivated = 0;      // if there is no crossing at the block, this value is ignored
        b.occupancy = 0;

        blocks.push_back(b);          // block structures sent to vector of all blocks
   }
}

/* PLC METHODS */
//---------------------------------------------------------------------------------
// Load the PLC file and parse it
void Region::loadPLC(QString filename) {
    plc->interpretHWPLC(filename);
}

/* CTC METHODS */
//---------------------------------------------------------------------------------
// Initialize speed and authority allowed in the region
void Region :: initialize(int db, float ss, std::vector<std::pair<int,int>> ac) {

    // assign speed, authority, and exit block
    exitBlock = db;
    std::cout << "exit block number is " << exitBlock << std::endl;

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
    blocks[b].occupancy = TrackModel::isBlockOccupied(line, b);
    return blocks[b].occupancy;
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

    }
}

/* GETTERS: INTERNAL METHODS */
//---------------------------------------------------------------------------------
std::string Region::getRoute() const {  // Line
    return route;
}

std::string Region::getSection(int b) const { // Section
    return blocks[b].section;
}

int Region::getCurrentBlock() const { // Current Block
    return iterator;
}

float Region::getSuggestedSpeed(int b) const{ // Suggested Speed
    return blocks[b].sugSpeed;
}

float Region::getCommandedSpeed(int b) const { // Commanded Speed
    return blocks[b].commSpeed;
}

float Region::getAuthority(int b) const{ // Authority
    return blocks[b].auth;
}

