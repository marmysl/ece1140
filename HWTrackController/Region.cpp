#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Region.hpp"

using namespace std;

//Constructor
Region :: Region() {

    iterator = 0;

    // Blue Line Track Layout Hardcoded for now, the SWTC will be sending the layout to this class
    region = 1;
    route = "Blue Line";
    std::vector<std::string> sec{"Y","A","A","A","A","A","A","A","A","A","A","A","A","A","A","A"};
    std::vector<int> blc{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    std::vector<bool> sw{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0};
    std::vector<bool> rc{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

   for (auto &it : blc){
        BlockInfo b;
        b.section = sec[it];
        b.blockID = blc[it];
        b.isSwitch = sw[it];
        b.isCrossing = rc[it];
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

// Initialize Region based on SWTC layout sent to the HW
Region::Region(std::vector<std::string> sec,std::vector<int> blc, std::vector<bool> sw, std::vector<bool> rc){
  region = 1;
  for (auto &it : blc){
      BlockInfo b;
      b.section = sec[it];
      b.blockID = blc[it];
      b.isSwitch = sw[it];
      b.isCrossing = rc[it];
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


void Region :: initialize(int db, float ss, std::vector<int> ac) {
    //setAuthority(ac, db);
    //setCommandedSpeed(ss, db);

    unsigned int i = 0;
    while (i < blocks.size()){
        blocks[i].sugSpeed = ss;
        blocks[i].commSpeed = ss;
        blocks[i].auth = ac[i];
        std:: cout << "Block " << i << " Speed and Authority: " << blocks[i].commSpeed << ", " << blocks[i].auth << std::endl;
        i++;
    }

    setCircuit();
}

std::string Region::getRoute() const {
    return route;
}

std::string Region::getSection(int b) const {
    return blocks[b].section;
}

int Region::getCurrentBlock() const {
    return iterator;
}

float Region::getSuggestedSpeed(int b) const{
    return blocks[b].sugSpeed;
}

float Region::getCommandedSpeed(int b) const {
    return blocks[b].commSpeed;
}

float Region::getAuthority(int b) const{
    return blocks[b].auth;
}

float Region::getSpeedLimit() const{
    // check that current block is equal to the input block (that could be included in the arguments)?
    TrackModel::Block *currentBlock;
    float speedLimit = currentBlock->speedLimit;
    return speedLimit;
}

void Region :: setCircuit() {
    for (unsigned int i = 0; i < blocks.size(); i++){
        TrackModel::TrackCircuitData tcdata = TrackModel::TrackCircuitData::fromFloat(blocks[i].commSpeed,blocks[i].auth);
        TrackModel::setTrackCircuit(route, blocks[i].blockID, tcdata);
        //std::cout << "Set Circuit: " << blocks[i].commSpeed << ", " << blocks[i].auth << std::endl;
    }
}

// CTC can access this whenever they wants
bool Region :: detectTrain(int b) {
    blocks[b].occupancy = TrackModel::isBlockOccupied("Blue Line", b);
    return blocks[b].occupancy;
}
