
#ifndef TRAINMODELUPDATEBLOCK_H
#define TRAINMODELUPDATEBLOCK_H
#include "../TrackModel/tracklayout.hpp"
#include "../TrackModel/trackmodel_train.hpp"
#include "../TrackModel/trackmodel_types.hpp"

#include <cstdint>
#include <string>

class TrainModelUpdateBlock
{

public:
    double blockDist;
    double blockGrade;
    double blockNum;
    std::string lineType;
    uint64_t trackCircuitData;
    uint64_t beaconData;
    int numPassengers;

    TrainModelUpdateBlock();
    void updateTrackInfo(bool);
    int updateBlock(int blockNum, bool first);
    double blockLength(int blockNum);
    double blockGradeUp(int blockNum);
    uint64_t updateTrackCircuit(int blockNum);
};

#endif // TRAINMODELUPDATEBLOCK_H

