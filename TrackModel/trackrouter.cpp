#include "trackrouter.h"
#include "tracklayout.hpp"

#include <queue>

namespace TrackModel {

TrainPathInfo::TrainPathInfo() {}

TrainPathInfo::~TrainPathInfo() {}

TrackRouter::TrackRouter( Route *route ) : layout(route)
{
    nodeCount = layout->blocks.size();
    nodeList = new PathNode[nodeCount];

    int i = 0;
    for( auto &kvp : layout->blocks )
    {
        nodeList[i].block = kvp.second;
        nodeMap.insert({kvp.second, nodeList + i});
        i++;
    }
}

TrackRouter::~TrackRouter()
{
    delete nodeList;
}

// find newly reachable nodes from this node
void TrackRouter::processLink( PathNode *curNode, BlockDir dir )
{
    Linkable *link = curNode->block->getLink(dir);

    // distance to next block is length of current block
    float newDist = curNode->distance + curNode->block->length;

    // if there is link in given direction
    if( link )
    {
        Block *straightBlock;

        // if the next link is a switch, then process the diverging line as well
        if( Switch *s = dynamic_cast<Switch *>(link) )
        {
            Block *branchBlock = s->divergeBlock;

            // if there is a diverging block (there should be or something is wonky)
            if( branchBlock )
            {
                PathNode *divNode = nodeMap[branchBlock];

                // check if we found a shorter path to that block, if so, chuck it in the queue with updated info
                if( newDist < divNode->distance )
                {
                    BlockDir entryDir = curNode->block->getEntryDir(branchBlock);

                    // only process if block is traversable in this dir
                    if( branchBlock->canTravelInDir(entryDir) )
                    {
                        // if the node was already found in the other direction then it's a loop, throw it out
                        if( divNode->dir == BLK_NODIR || entryDir == divNode->dir )
                        {
                            divNode->dir = entryDir;
                            divNode->distance = newDist;
                            divNode->prev = curNode;

                            divNode->prevSwitch = s;
                            divNode->switchDir = SW_DIVERGING;

                            pathQueue.push(divNode);
                        }
                    }
                }
            }

            straightBlock = s->straightBlock;
        }
        else straightBlock = link->getTarget();

        PathNode *straightNode = nodeMap[straightBlock];

        // check if we found a shorter path to that block, if so, chuck it in the queue with updated info
        if( newDist < straightNode->distance )
        {
            BlockDir entryDir = curNode->block->getEntryDir(straightBlock);

            // only process if block is traversable in this dir
            if( straightBlock->canTravelInDir(entryDir) )
            {
                // if the node was already found in the other direction then it's a loop, throw it out
                if( straightNode->dir == BLK_NODIR || entryDir == straightNode->dir )
                {
                    straightNode->dir = entryDir;
                    straightNode->distance = newDist;
                    straightNode->prev = curNode;

                    // if we got here via the straight leg of the switch
                    if( Switch *s = dynamic_cast<Switch *>(link) )
                    {
                        straightNode->prevSwitch = s;
                        straightNode->switchDir = SW_STRAIGHT;
                    }

                    pathQueue.push(straightNode);
                }
            }
        }
    }
}

// Dijkstra's algo
TrainPathInfo TrackRouter::findPath( int startBlock, BlockDir startDir, int endBlock )
{
    pathQueue = PathQueueType();

    for( int i = 0; i < nodeCount; i++ )
    {
        nodeList[i].distance = std::numeric_limits<float>::infinity();
        nodeList[i].dir = BLK_NODIR;
        nodeList[i].prev = nullptr;
        nodeList[i].prevSwitch = nullptr;

        if( nodeList[i].block->id == startBlock )
        {
            nodeList[i].distance = 0;

            if( nodeList[i].block->oneWay != BLK_NODIR )
            {
                nodeList[i].dir = nodeList[i].block->oneWay;
            }
            else nodeList[i].dir = startDir;

            pathQueue.push(nodeList + i);
        }
    }

    PathNode *curNode;

    while( !pathQueue.empty() )
    {
        curNode = pathQueue.top();
        pathQueue.pop();

        // if we reached the dest block, we know we found the shortest path
        if( curNode->block->id == endBlock )
        {
            // return path
            TrainPathInfo path;

            // push blocks from last to first
            for( PathNode *n = curNode; n != nullptr; n = n->prev )
            {
                path.blocks.push_back(n->block);

                if( n->prevSwitch )
                {
                    path.switchStates.push_back({n->prevSwitch->fromBlock->id, n->switchDir});
                }
            }

            std::reverse(path.blocks.begin(), path.blocks.end());
            std::reverse(path.switchStates.begin(), path.switchStates.end());

            return path;
        }

        // add the newly reachable block(s) to the processing queue

        // check for blocks in forward direction for forward or bidirectional search
        if( curNode->dir != BLK_REVERSE )
        {
            processLink(curNode, BLK_FORWARD);
        }

        // Check for blocks in reverse direction for reverse or bidirectional search
        if( curNode->dir != BLK_FORWARD )
        {
            processLink(curNode, BLK_REVERSE);
        }
    }

    return TrainPathInfo();
}

}
