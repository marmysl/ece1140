#include "../TrackModel/trackmodel.cpp"
//#include "../TrackModel/tracklayout.hpp"
#include "../TrackModel/tracklayout.cpp"
//#include "../TrackModel/trackmodel_train.hpp"
//#include "../TrackModel/trackmodel_types.hpp"
#include <cstdint>
#include <string>

using namespace TrackModel;

class TrainModelUpdateBlock
{
    public:
        TrainModelUpdateBlock()
        {

        }

        static int updateBlock(int blockNum){
            std::string line = "Blue Line";
            removeOccupancy(line, blockNum);
            blockNum = blockNum + 1;
            addOccupancy(line, blockNum);
            return blockNum;
        }

        static double blockLength(int blockNum){
            std::string line = "Blue Line";
            Route *blueLine = getRoute(line);
            Block* blockInfo = blueLine -> getBlock(blockNum);
            double blockDist = blockInfo -> length;
            return blockDist;
        }

        static double blockGrade(int blockNum){
            std::string line = "Blue Line";
            Route *blueLine = getRoute(line);
            Block* blockInfo = blueLine -> getBlock(blockNum);
            double newBlockGrade = blockInfo -> grade;
            return newBlockGrade;
        }

        static uint64_t updateTrackCircuit(int blockNum){
            std::string line = "Blue Line";
            TrackCircuitData newData = getTrackCircuit(line, blockNum);
            uint64_t trackCircuitData = newData.getEncodedData();
            return trackCircuitData;
        }
};

/*
TrainModelUpdateBlock();
static int updateBlock(int blockNum);
static double blockLength(int blockNum);
static double blockGrade(int blockNum);
static uint64_t updateTrackCircuit(int blockNum);

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
