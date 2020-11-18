
#ifndef TRAINMODELUPDATEBLOCK_H
#define TRAINMODELUPDATEBLOCK_H
#include "../TrackModel/tracklayout.hpp"
#include "../TrackModel/trackmodel_train.hpp"
#include "../TrackModel/trackmodel_types.hpp"

#include <cstdint>
#include <string>

using namespace std;

class TrainModelUpdateBlock
{
public:
    double blockDist;
    double blockGrade;
    int blockNum;
    TrackModel::Route *route;
    TrackModel::Block *block;
    TrackModel::BlockDir blockDir;
    TrackModel::NextBlockData blockData;
    std::string lineType;
    uint64_t trackCircuitData;
    TrackModel::BeaconData beaconData;
    int numPassengers = 0;

    TrainModelUpdateBlock(std::string);
    void updateTrackInfo(bool);
    void updateBlock(bool first);
    void blockLength();
    void blockGradeUp();
    void updateTrackCircuit();
    void updateBeaconData();
};

#endif //TRAINMODELUPDATEBLOCK_H

