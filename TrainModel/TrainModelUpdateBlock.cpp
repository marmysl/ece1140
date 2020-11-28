#include "TrackModel/tracklayout.hpp"
#include "TrackModel/trackmodel_train.hpp"
#include "TrainModelUpdateBlock.h"
#include <cstdint>
#include <string>
#include <iostream>

TrainModelUpdateBlock::TrainModelUpdateBlock(std::string lineTypeNew) {
    lineType = lineTypeNew;
    blockDist = 0;
    blockGrade = 0;
    blockNum = 0;
    route = TrackModel::getRoute(lineType);
    block = route->getBlock(0);
    blockDir = TrackModel::BLK_FORWARD;
    updateTrackCircuit();
    updateBeaconData();

}

void TrainModelUpdateBlock::updateTrackInfo(bool inYard){
    //update block num
    //update block length
    //send occupancy to Track Model
    updateBlock(inYard);
    blockLength();
    blockGradeUp();
    updateTrackCircuit();
    updateBeaconData();
}

void TrainModelUpdateBlock::updateBlock(bool first){
    if (!first){TrackModel::removeOccupancy(lineType, blockNum);}
    blockData = block->getNextBlock(blockDir);
    block = blockData.block;
    blockDir = blockData.entryDir;
    blockNum = block->id;
    TrackModel::addOccupancy(lineType, blockNum);
}

void TrainModelUpdateBlock::updateBeaconData(){
    beaconData = block->getBeaconInDir(blockDir);
}

void TrainModelUpdateBlock::blockLength(){
    TrackModel::Block* blockInfo = route -> getBlock(blockNum);
    blockDist = blockInfo -> length;
}

void TrainModelUpdateBlock::blockGradeUp(){
    TrackModel::Block* blockInfo = route -> getBlock(blockNum);
    blockGrade = blockInfo -> grade;
}

void TrainModelUpdateBlock::updateTrackCircuit(){
    TrackModel::TrackCircuitData newData = TrackModel::getTrackCircuit(lineType, blockNum);
    trackCircuitData = newData.getEncodedData();
}

int TrainModelUpdateBlock::getPassengers(int maxPassengers){
    int numPassengers;
    TrackModel::PlatformData platform = block->getPlatformInDir(blockDir);
    numPassengers = TrackModel::takePassengers(lineType, platform.station->name, maxPassengers);
    return numPassengers;
}
