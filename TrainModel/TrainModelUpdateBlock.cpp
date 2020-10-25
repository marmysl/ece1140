#include "TrackModel/tracklayout.hpp"
#include "TrackModel/trackmodel_train.hpp"
#include "TrainModelUpdateBlock.h"
#include <cstdint>
#include <string>

using namespace TrackModel;

TrainModelUpdateBlock::TrainModelUpdateBlock() {}

void TrainModelUpdateBlock::updateTrackInfo(bool inYard){
    //update block num
    //update block length
    //send occupancy to Track Model
    blockNum = this->updateBlock(blockNum, inYard);
    blockDist = this->blockLength(blockNum);
    blockGrade = TrainModelUpdateBlock::blockGradeUp(blockNum);
    this->updateTrackCircuit(blockNum);
}

int TrainModelUpdateBlock::updateBlock(int blockNum, bool first){
    std::string line = "Blue Line";
    if (!first){removeOccupancy(line, blockNum);}
    blockNum = blockNum + 1;
    addOccupancy(line, blockNum);
    return blockNum;
}

double TrainModelUpdateBlock::blockLength(int blockNum){
    std::string line = "Blue Line";
    Route *blueLine = getRoute(line);
    Block* blockInfo = blueLine -> getBlock(blockNum);
    double blockDist = blockInfo -> length;
    return blockDist;
}

double TrainModelUpdateBlock::blockGradeUp(int blockNum){
    std::string line = "Blue Line";
    Route *blueLine = getRoute(line);
    Block* blockInfo = blueLine -> getBlock(blockNum);
    double newBlockGrade = blockInfo -> grade;
    return newBlockGrade;
}

uint64_t TrainModelUpdateBlock::updateTrackCircuit(int blockNum){
    std::string line = "Blue Line";
    TrackCircuitData newData = getTrackCircuit(line, blockNum);
    uint64_t trackCircuitData = newData.getEncodedData();
    return trackCircuitData;
}
