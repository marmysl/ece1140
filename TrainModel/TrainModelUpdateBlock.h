/*#ifndef TRAINMODELUPDATEBLOCK_H
#define TRAINMODELUPDATEBLOCK_H
#include "../TrackModel/trackmodel.cpp"
#include "../TrackModel/tracklayout.hpp"
#include "../TrackModel/tracklayout.cpp"
#include "../TrackModel/trackmodel_train.hpp"
#include "../TrackModel/trackmodel_types.hpp"
#include <cstdint>
#include <string>

class TrainModelUpdateBlock
{
public:
    TrainModelUpdateBlock();
    static int updateBlock(int blockNum);
    static double blockLength(int blockNum);
    static double blockGrade(int blockNum);
    static uint64_t updateTrackCircuit(int blockNum);
};

#endif // TRAINMODELUPDATEBLOCK_H*/

