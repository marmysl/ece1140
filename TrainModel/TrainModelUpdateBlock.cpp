#include "TrackModel/tracklayout.hpp"
#include "TrackModel/trackmodel_train.hpp"
#include "TrainModelUpdateBlock.h"
#include <cstdint>
#include <string>

TrainModelUpdateBlock::TrainModelUpdateBlock() {
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
    std::string line = "Blue Line";
    if (!first){TrackModel::removeOccupancy(line, blockNum);}
    blockNum = blockNum + 1;
    TrackModel::addOccupancy(line, blockNum);
}

void TrainModelUpdateBlock::blockLength(){
    std::string line = "Blue Line";
    TrackModel::Route *blueLine = TrackModel::getRoute(line);
    TrackModel::Block* blockInfo = blueLine -> getBlock(blockNum);
    blockDist = blockInfo -> length;
}

void TrainModelUpdateBlock::blockGradeUp(){
    std::string line = "Blue Line";
    TrackModel::Route *blueLine = TrackModel::getRoute(line);
    TrackModel::Block* blockInfo = blueLine -> getBlock(blockNum);
    blockGrade = blockInfo -> grade;
}

void TrainModelUpdateBlock::updateTrackCircuit(){
    std::string line = "Blue Line";
    TrackModel::TrackCircuitData newData = TrackModel::getTrackCircuit(line, blockNum);
    trackCircuitData = newData.getEncodedData();
}
