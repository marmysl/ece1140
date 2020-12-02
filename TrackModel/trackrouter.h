#pragma once
#include "tracklayout.hpp"
#include <queue>

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
            Switch *prevSwitch;
            SwitchState switchDir;
        };

    private:
        /*! Min heap node comparator */
        struct compNodes
        {
            bool operator() ( const PathNode *a, const PathNode *b ) const
            {
                return a->distance > b->distance;
            }
        };

        using PathQueueType = std::priority_queue<PathNode*, std::vector<PathNode*>, compNodes>;

        Route *layout;
        PathNode *nodeList;
        std::unordered_map<Block *, PathNode *> nodeMap;
        PathQueueType pathQueue;
        int nodeCount;

    public:

        TrackRouter( Route *route );
        ~TrackRouter();

        TrainPathInfo findPath( int startBlock, BlockDir startDir, int endBlock );

    private:
        void processLink( PathNode *curNode, BlockDir dir );
    };
}
