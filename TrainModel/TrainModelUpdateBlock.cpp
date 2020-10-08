
#include "TrackModel/tracklayout.hpp"
#include "TrackModel/trackmodel_train.hpp"
#include "TrainModelUpdateBlock.h"
#include <cstdint>
#include <string>

using namespace TrackModel;

TrainModelUpdateBlock::TrainModelUpdateBlock() {}

int TrainModelUpdateBlock::updateBlock(int blockNum){
    std::string line = "Blue Line";
    removeOccupancy(line, blockNum);
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

double TrainModelUpdateBlock::blockGrade(int blockNum){
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

/*
#include "TrainModelUpdateBlock.h"
#include <cstdint>
#include <string>

TrainModelUpdateBlock::TrainModelUpdateBlock()
{

}

int TrainModelUpdateBlock::updateBlock(int blockNum){
    std::string line = "Blue Line";
    removeOccupancy(line, blockNum);
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

double TrainModelUpdateBlock::blockGrade(int blockNum){
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

*/
