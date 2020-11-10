#include "TrackModel/tracklayout.hpp"
#include "TrackModel/trackmodel_train.hpp"
#include "TrainModelUpdateBlock.h"
#include <cstdint>
#include <string>

TrainModelUpdateBlock::TrainModelUpdateBlock(std::string lineTypeNew) {
    lineType = lineTypeNew;
    blockDist = 0;
    blockGrade = 0;
    blockNum = 0;
}

void TrainModelUpdateBlock::updateTrackInfo(bool inYard){
    //update block num
    //update block length
    //send occupancy to Track Model
    updateBlock(inYard);
    blockLength();
    blockGradeUp();
    updateTrackCircuit();
}

void TrainModelUpdateBlock::updateBlock(bool first){
    if (!first){TrackModel::removeOccupancy(lineType, blockNum);}
    blockNum = blockNum + 1;
    TrackModel::addOccupancy(lineType, blockNum);
}

void TrainModelUpdateBlock::blockLength(){
    TrackModel::Route *blueLine = TrackModel::getRoute(lineType);
    TrackModel::Block* blockInfo = blueLine -> getBlock(blockNum);
    blockDist = blockInfo -> length;
}

void TrainModelUpdateBlock::blockGradeUp(){
    TrackModel::Route *blueLine = TrackModel::getRoute(lineType);
    TrackModel::Block* blockInfo = blueLine -> getBlock(blockNum);
    blockGrade = blockInfo -> grade;
}

void TrainModelUpdateBlock::updateTrackCircuit(){
    TrackModel::TrackCircuitData newData = TrackModel::getTrackCircuit(lineType, blockNum);
    trackCircuitData = newData.getEncodedData();
}
