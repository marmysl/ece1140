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
        std::vector<PathNode *> dynamicNodes;
        PathQueueType pathQueue;
        int nodeCount;

    public:

        TrackRouter( Route *route );
        ~TrackRouter();

        /*! Perform a simplified djikstra search for a path between two blocks */
        TrainPathInfo findPath( int startBlock, BlockDir startDir, int endBlock );

    private:
        /*! Find newly reachable blocks from the given block/node */
        void processLink( PathNode *curNode, BlockDir dir );

        /*! Free all dynamically allocated nodes */
        void freeDynamicNodes();
    };
}
