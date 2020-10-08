#include "TrainModelUpdateBlock.h"
#include "tracklayout.hpp"
#include "trackmodel_train.hpp"
#include "trackmodel_types.hpp"
using namespace TrackModel;
#include <cstdint>

TrainModelUpdateBlock::TrainModelUpdateBlock()
{

}

int TrainModelUpdateBlock::updateBlock(int blockNum){
<<<<<<< Updated upstream
    Route *blueLine = getRoute("Blue Line");
    trackmodel_train::removeOccupancy(blueLine, blockNum);
    blockNum = blockNum + 1;
    trackmodel_train::addOccupancy(blueLine, blockNum);
=======
    std::string line = "Blue Line";
    removeOccupancy(line, blockNum);
    blockNum = blockNum + 1;
    addOccupancy(line, blockNum);
>>>>>>> Stashed changes
    return blockNum;
}

double TrainModelUpdateBlock::blockLength(int blockNum){
    Route *blueLine = getRoute("Blue Line");
    Block* blockInfo = blueLine.getBlock(blockNum);
    double blockDist = blockInfo.length;
    return blockDist;
}

double TrainModelUpdateBlock::blockGrade(int blockNum){
    Route *blueLine = getRoute("Blue Line");
    Block* blockInfo = blueLine.getBlock(blockNum);
    double newBlockGrade = blockInfo.grade;
    return newBlockGrade;
}

uint64_t TrainModelUpdateBlock::updateTrackCircuit(int blockNum){
<<<<<<< Updated upstream
    TrackCircuitData newData = trackmodel_train::getTrackCircuit("Blue Line", blockNum);
=======
    std::string line = "Blue Line";
    TrackCircuitData newData = getTrackCircuit(line, blockNum);
>>>>>>> Stashed changes
    uint64_t trackCircuitData = newData.getEncodedData();
    return trackCircuitData;
}

