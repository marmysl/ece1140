#include "TrainModelUpdateBlock.h"
using namespace TrackModel;
#include <cstdint>

TrainModelUpdateBlock::TrainModelUpdateBlock()
{

}

int TrainModelUpdateBlock::updateBlock(int blockNum){
    std::string line = "Blue Line";
    Route *blueLine = getRoute(line);
    removeOccupancy("Blue Line", blockNum);
    blockNum = blockNum + 1;
    addOccupancy("Blue Line", blockNum);
    return blockNum;
}

double TrainModelUpdateBlock::blockLength(int blockNum){
    std::string line = "Blue Line";
    Route *blueLine = getRoute(line);
    Block* blockInfo = blueLine -> getBlock(blockNum);
    double blockDist = blockInfo -> length;
    return blockDist;
}

double TrainModelUpdateBlock::blockGrade(int blockNum){
    std::string line = "Blue Line";
    Route *blueLine = getRoute(line);
    Block* blockInfo = blueLine -> getBlock(blockNum);
    double newBlockGrade = blockInfo -> grade;
    return newBlockGrade;
}

uint64_t TrainModelUpdateBlock::updateTrackCircuit(int blockNum){
    TrackCircuitData newData = getTrackCircuit("Blue Line", blockNum);
    uint64_t trackCircuitData = newData.getEncodedData();
    return trackCircuitData;
}

