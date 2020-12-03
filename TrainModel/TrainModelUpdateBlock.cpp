/**
 * This class handles updating the block and associated block data as the train moves down the track.
 *
 * Blocks and associated structs used are accessed from the Track Model. The track model holds the linked list that will
 * pass the next block to the train model on the given route.
 *
*/
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

// Function that updates the track information,  calls appropriate functions
void TrainModelUpdateBlock::updateTrackInfo(bool inYard){
    updateBlock(inYard);
    blockLength();
    blockGradeUp();
    updateTrackCircuit();
    updateBeaconData();
}

// Funtion that updates the block of the train to the next one on route
void TrainModelUpdateBlock::updateBlock(bool first){
    //remove occupancy through Track Model
    if (!first){TrackModel::removeOccupancy(lineType, blockNum);}

    //get the next block
    blockData = block->getNextBlock(blockDir);
    block = blockData.block;
    blockDir = blockData.entryDir;
    blockNum = block->id;

    //add occupancy of train through the Track Model
    TrackModel::addOccupancy(lineType, blockNum);
}

// Function to get beacon data of the current block
void TrainModelUpdateBlock::updateBeaconData(){
    beaconData = block->getBeaconInDir(blockDir);
}

// Function to get the length of the current block
void TrainModelUpdateBlock::blockLength(){
    TrackModel::Block* blockInfo = route -> getBlock(blockNum);
    blockDist = blockInfo -> length;
}

// Function to get the grade of the current block
void TrainModelUpdateBlock::blockGradeUp(){
    TrackModel::Block* blockInfo = route -> getBlock(blockNum);
    blockGrade = blockInfo -> grade;
}

// Function to get the track circuit of the current block
void TrainModelUpdateBlock::updateTrackCircuit(){
    TrackModel::TrackCircuitData newData = TrackModel::getTrackCircuit(lineType, blockNum);
    trackCircuitData = newData.getEncodedData();
}

// Function to get the passengers available at a station
int TrainModelUpdateBlock::getPassengers(int maxPassengers){
    int numPassengers = 0;

    // first check if a platform exists at that block
    if (block->platform.exists()){
        //If platform exists, take passengers from it
        TrackModel::PlatformData platform = block->getPlatformInDir(blockDir);
        numPassengers = TrackModel::takePassengers(lineType, platform.station->name, maxPassengers);
    }
    return numPassengers;
}
