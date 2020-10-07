#ifndef TRAINMODELUPDATEBLOCK_H
#define TRAINMODELUPDATEBLOCK_H
#include "tracklayout.hpp"
#include "trackmodel_train.hpp"
#include "trackmodel_types.hpp"
#include <cstdint>

class TrainModelUpdateBlock
{
public:
    TrainModelUpdateBlock();
    static int updateBlock(int blockNum);
    static double blockLength(int blockNum);
    static double blockGrade(int blockNum);
    static uint64_t updateTrackCircuit(int blockNum);
};

#endif // TRAINMODELUPDATEBLOCK_H