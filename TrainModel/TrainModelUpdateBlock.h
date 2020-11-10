
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
    std::string lineType;
    uint64_t trackCircuitData;
    uint64_t beaconData;
    int numPassengers = 0;

    TrainModelUpdateBlock(std::string);
    void updateTrackInfo(bool);
    void updateBlock(bool first);
    void blockLength();
    void blockGradeUp();
    void updateTrackCircuit();
};

#endif //TRAINMODELUPDATEBLOCK_H

