#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Region.hpp"

using namespace std;

//Constructor
Region :: Region() {
    region = 1;
//    route = "Blue Line";
//    cout << "Route: " << route << endl;
}

// Initialize Region based on SWTC layout sent to the HW
Region::Region(std::vector<std::string> sec,std::vector<int> blc, std::vector<bool> sw, std::vector<bool> rc){
  region = 1;
  for (int i=0; i < blc.size(); i++){
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


//void Region :: initialize(CTCSignals &ctc) {
//    int db = ctc.getDestBlock();
//    float ac = ctc.getAuth();
//    float ss = ctc.getSpeed();
//    //setAuthority(ac, db);
//    //setCommandedSpeed(ss, db);

//    for (int i = 0; i < blocks.size(); i++){
//        blocks[i].sugSpeed = ss;
//        blocks[i].commSpeed = ss;
//        blocks[i].auth = ac;
//    }

//    setCircuit();
//}

std::string Region::getRoute() const {
    return route;
}

std::string Region::getSection(int b) const {
    return blocks[b].section;
}

int Region::getCurrentBlock(int b) const { // lol
    return b;
}

float Region::getSuggestedSpeed() const{
    return suggestedSpeed;
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
    float speedLimit = currentBlock -> speedLimit;
    return speedLimit;
}

void Region :: setCircuit() {
    for (int i = 0; i < blocks.size(); i++){
        TrackModel::TrackCircuitData tcdata = TrackModel::TrackCircuitData::fromFloat(blocks[i].commSpeed,blocks[i].auth);
        TrackModel::setTrackCircuit(route, blocks[i].blockID, tcdata);
    }
}

bool Region :: detectTrain(int b) {
    blocks[b-1].occupancy = TrackModel::isBlockOccupied("Blue Line", b);
    cout << " train detected is " << blocks[b-1].occupancy << endl;
    return blocks[b-1].occupancy;
}


//void Region ::setAuthority(int ac)
//{
//    float blockLength = 50;
//    float trackLength;

//    if(blocknum > 11){
//       blocknum -= 5;
//    }

//    if(station == "Station B" && blocknum == -1){
//        int m = 0;
//        trackLength = 10 * blockLength;

//        for(int i = 0; i < 10; i++){
//            authority.push_back(0);
//        }
//        for(auto i = authority.begin(); i != authority.end(); i++){
//            if(m == 0){
//                *i = trackLength;
//            }
//            else{
//                *i = authority.at(m-1) - blockLength;
//            }
//            m++;
//        }
//    }
//    else if(station == "Station C" && blocknum == -1){
//        int n = 0;
//        trackLength = 10 * blockLength;

//        for(int i = 0; i < 10; i++){
//            authority.push_back(0);
//        }
//        for(auto i = authority.begin(); i != authority.end(); i++){
//            if(n == 0){
//                *i = trackLength;
//            }
//            else{
//                *i = authority.at(n-1) - blockLength;
//            }
//            n++;
//        }
//    }
//    else if(blocknum != -1 && station == "-1"){
//        int o = 0;
//        trackLength = blocknum * blockLength;

//        for(int i = 0; i < blocknum; i++){
//            authority.push_back(0);
//        }
//        for(auto i = authority.begin(); i != authority.end(); i++){
//            if(o == 0){
//                *i = trackLength;
//            }
//            else{
//                *i = authority.at(o-1) - blockLength;
//            }
//            o++;
//        }
//    }
//    else{
//        return;
//    }
//}

//void CTCDispatch::setSpeed(std::string station, int blocknum, float timeStart, float timeArrival)
//{
//    float duration = timeArrival - timeStart;
//    float blockLength = 50;
//    float trackLength;
//    float avgspeed;

//    if(duration <= 0){
//        qDebug() << "Invalid time frame: please try again.";
//        return;
//    }

//    if(blocknum > 11){
//       blocknum -= 5;
//    }

//    int m = 0;

//    if(station == "Station B" && blocknum == -1){
//        trackLength = 10 * blockLength;
//        avgspeed = trackLength/duration;

//        qDebug() << "Track Length: " << QString::number(trackLength);
//        qDebug() << "Average Speed: " << QString::number(avgspeed);

//        for(int i = 0; i < 10; i++){
//            speed.push_back(0);
//        }
//        for(auto i = speed.begin(); i != speed.end(); i++){
//            if(m < 3){
//                *i = (1.666666 * avgspeed);
//            }
//            else if(m >= 3 && m < 6){
//                *i = avgspeed;
//            }
//            else{
//                *i = ((-avgspeed*(m+1)) + (10*avgspeed))/4;
//            }
//            m++;
//        }
//    }
//    else if(station == "Station C" && blocknum == -1){
//        trackLength = 10 * blockLength;
//        avgspeed = trackLength/duration;

//        qDebug() << "Track Length: " << QString::number(trackLength);
//        qDebug() << "Average Speed: " << QString::number(avgspeed);

//        for(int i = 0; i < 10; i++){
//            speed.push_back(0);
//        }
//        for(auto i = speed.begin(); i != speed.end(); i++){
//            if(m < 3){
//                *i = (1.666666 * avgspeed);
//            }
//            else if(m >= 3 && m < 6){
//                *i = avgspeed;
//            }
//            else{
//                *i = ((-avgspeed*(m+1)) + (10*avgspeed))/4;
//            }
//            m++;
//        }
//    }
//    else if(blocknum != -1 && station == "-1"){
//        trackLength = blocknum * blockLength;
//        avgspeed = trackLength/duration;

//        for(int i = 0; i < blocknum; i++){
//            speed.push_back(0);
//        }
//        for(auto i = speed.begin(); i != speed.end(); i++){
//            *i = avgspeed;
//        }
//    }
//}
