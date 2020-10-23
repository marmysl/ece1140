#pragma once
#include "tracklayout.hpp"

namespace TrackModel
{
    class TrainPathInfo
    {
    public:
        std::vector<Block *> blocks;
        std::vector<std::pair<int, SwitchState>> switchStates;

        TrainPathInfo();
        ~TrainPathInfo();
    };

    class TrackRouter
    {
        struct PathNode
        {
            Block *block;
            BlockDir dir;
            float distance;

            PathNode *prev;
            int hopCount;
        };

    private:
        Route *layout;
        PathNode *nodeList;
        std::unordered_map<Block *, PathNode *> nodeMap;
        int nodeCount;

    public:
        TrackRouter( Route *route );
        ~TrackRouter();

        TrainPathInfo findPath( int startBlock, BlockDir startDir, int endBlock );
    };
}
