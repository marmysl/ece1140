#include "trackrouter.h"
#include "tracklayout.hpp"

#include <queue>

namespace TrackModel {

TrainPathInfo::TrainPathInfo() {}

TrainPathInfo::~TrainPathInfo() {}

TrackRouter::TrackRouter( Route *route ) : layout(route)
{
    nodeCount = layout->blocks.size() + 1;
    nodeList = new PathNode[nodeCount];

    nodeList[0].block = yard;
    nodeMap.insert({yard, nodeList});

    int i = 1;
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


// Dijkstra's algo
TrainPathInfo TrackRouter::findPath( int startBlock, BlockDir startDir, int endBlock )
{
    struct compNodes
    {
        bool operator() ( const PathNode *a, const PathNode *b ) const
        {
            return a->distance > b->distance;
        }
    };

    std::priority_queue<PathNode*, std::vector<PathNode*>, compNodes> pathQueue;

    for( int i = 0; i < nodeCount; i++ )
    {
        nodeList[i].distance = std::numeric_limits<float>::infinity();
        nodeList[i].dir = BLK_NODIR;
        nodeList[i].prev = nullptr;
        nodeList[i].hopCount = 0;

        if( nodeList[i].block->id == startBlock )
        {
            nodeList[i].distance = 0;
            nodeList[i].dir = startDir;
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
            }

            std::reverse(path.blocks.begin(), path.blocks.end());
            return path;
        }

        // add the newly reachable block(s) to the processing queue
        float newDist = curNode->distance + curNode->block->length; // add block length to total distance from start

        if( curNode->dir != BLK_REVERSE )
        {
            // forward or both dirs
            Linkable *next = curNode->block->forwardLink;

            if( next )
            {
                Block *straight;

                // if the next link is a switch, then process the diverging line as well
                if( Switch *s = dynamic_cast<Switch *>(next) )
                {
                    Block *diverge = s->divergeBlock;

                    if( diverge )
                    {
                        PathNode *d = nodeMap[diverge];

                        // check if we found a shorter path to that block, if so, chuck it in the queue with updated info
                        if( newDist < d->distance )
                        {
                            // if cur block is previous of next, then next dir = fwd
                            BlockDir searchDir;
                            if( d->block->reverseLink == curNode->block ) searchDir = BLK_FORWARD;
                            else searchDir = BLK_REVERSE;

                            // if the node was already found in the other direction then it's a loop, throw it out
                            if( d->dir == BLK_NODIR || searchDir == d->dir )
                            {
                                d->dir = searchDir;
                                d->distance = newDist;
                                d->prev = curNode;

                                pathQueue.push(d);
                            }
                        }
                    }

                    straight = s->straightBlock;
                }
                else straight = next->getTarget();

                PathNode *n = nodeMap[straight];

                // check if we found a shorter path to that block, if so, chuck it in the queue with updated info
                if( newDist < n->distance )
                {
                    // if cur block is previous of next, then next dir = fwd
                    BlockDir searchDir;
                    if( n->block->reverseLink == curNode->block ) searchDir = BLK_FORWARD;
                    else searchDir = BLK_REVERSE;

                    // if the node was already found in the other direction then it's a loop, throw it out
                    if( n->dir == BLK_NODIR || searchDir == n->dir )
                    {
                        n->dir = searchDir;
                        n->distance = newDist;
                        n->prev = curNode;

                        pathQueue.push(n);
                    }
                }
            }
        }

        // Check for blocks in reverse direction for reverse or unidirectional search
        if( curNode->dir != BLK_FORWARD )
        {
            Linkable *prev = curNode->block->reverseLink;

            if( prev )
            {
                Block *straight;

                // if the next link is a switch, then process the diverging line as well
                if( Switch *s = dynamic_cast<Switch *>(prev) )
                {
                    Block *diverge = s->divergeBlock;

                    if( diverge )
                    {
                        PathNode *d = nodeMap[diverge];

                        // check if we found a shorter path to that block, if so, chuck it in the queue with updated info
                        if( newDist < d->distance )
                        {
                            // if cur block is previous of next, then next dir = fwd
                            BlockDir searchDir;
                            if( d->block->reverseLink == curNode->block ) searchDir = BLK_REVERSE;
                            else searchDir = BLK_FORWARD;

                            // if the node was already found in the other direction then it's a loop, throw it out
                            if( d->dir == BLK_NODIR || searchDir == d->dir )
                            {
                                d->dir = searchDir;
                                d->distance = newDist;
                                d->prev = curNode;

                                pathQueue.push(d);
                            }
                        }
                    }

                    straight = s->straightBlock;
                }
                else straight = prev->getTarget();

                PathNode *n = nodeMap[straight];

                // check if we found a shorter path to that block, if so, chuck it in the queue with updated info
                if( newDist < n->distance )
                {
                    // if cur block is previous of next, then next dir = fwd
                    BlockDir searchDir;
                    if( n->block->reverseLink == curNode->block ) searchDir = BLK_REVERSE;
                    else searchDir = BLK_FORWARD;

                    // if the node was already found in the other direction then it's a loop, throw it out
                    if( n->dir == BLK_NODIR || searchDir == n->dir )
                    {
                        n->distance = newDist;
                        n->prev = curNode;

                        pathQueue.push(n);
                    }
                }
            }
        }
    }

    return TrainPathInfo();
}

}
