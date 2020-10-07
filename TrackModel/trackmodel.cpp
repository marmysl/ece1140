#include <iostream>
#include <unordered_map>
#include "tracklayout.hpp"

namespace TrackModel {
    struct BlockStatus {
        TrackCircuitData circuit;
        int trainCount;
        BlockFault faults;

        BlockStatus() : circuit(TrackCircuitData()), trainCount(0), faults(FAULT_NONE) {}
    };

    struct RouteStatus {
        std::unordered_map<int, BlockStatus *> blockMap;

        RouteStatus() : blockMap(std::unordered_map<int, BlockStatus *>()) {}
    };

    std::unordered_map<std::string, RouteStatus *> routeStatusMap = std::unordered_map<std::string, RouteStatus *>();

    // Track Controller Interface
    //---------------------------------------------------------------------------------
    void setTrackCircuit( std::string route, int blockId, TrackCircuitData data ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(blockId);
            blockInfo->circuit = data;
        }
        catch( const std::out_of_range &e ) {
            throw std::invalid_argument("route or block not found");
        }
    }

    bool isBlockOccupied( std::string route, int blockId ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(blockId);
            return blockInfo->trainCount > 0;
        }
        catch( const std::invalid_argument &e ) {
            throw std::invalid_argument("route or block not found");
        }
    }

    BlockFault getFaults( std::string route, int blockId ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(blockId);
            return blockInfo->faults;
        }
        catch( const std::out_of_range &e ) {
            throw std::invalid_argument("route or block not found");
        }
    }

    SwitchState getSwitchState( Route *route, int switchBlockId ) {
        Switch *s = route->getSwitch(switchBlockId);

        if( s == NULL ) throw std::invalid_argument("Requested switch not found");
        return s->direction;
    }

    void setSwitchState( Route *route, int switchBlockId, SwitchState newDirection ) {
        Switch *s = route->getSwitch(switchBlockId);

        if( s == NULL ) throw std::invalid_argument("Requested switch not found");
        s->setDirection(newDirection);
    }


    // Train Model Interface
    //---------------------------------------------------------------------------------
    TrackCircuitData getTrackCircuit( std::string route, int blockId ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(blockId);
            return blockInfo->circuit;
        }
        catch( const std::out_of_range &e ) {
            throw std::invalid_argument("route or block not found");
        }
    }

    void addOccupancy( std::string route, int blockId ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(blockId);
            blockInfo->trainCount += 1;
        }
        catch( const std::out_of_range &e ) {
            throw std::invalid_argument("route or block not found");
        }
    }

    void removeOccupancy( std::string route, int blockId ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(blockId);
            blockInfo->trainCount -= 1;
        }
        catch( const std::out_of_range &e ) {
            throw std::invalid_argument("route or block not found");
        }
    }


    // Track Model Internal
    //---------------------------------------------------------------------------------

    void initRouteState( Route *route ) {
        RouteStatus *rs = new RouteStatus();
        routeStatusMap[route->name] = rs;
        
        for( auto kvp : route->blocks ) {
            rs->blockMap[kvp.second->id] = new BlockStatus();
        }
    }

    // apply the given fault to this block
    // returns: the new fault state
    BlockFault setFault( std::string route, int block, BlockFault fault ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(block);

            blockInfo->faults = blockInfo->faults | fault;
            return blockInfo->faults;
        }
        catch( const std::out_of_range &e ) {
            throw std::invalid_argument("route or block not found");
        }
    }

    // remove the given fault from this block
    // returns: the new fault state
    BlockFault clearFault( std::string route, int block,  BlockFault fault ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(block);

            blockInfo->faults = blockInfo->faults & ~fault;
            return blockInfo->faults;
        }
        catch( const std::out_of_range &e ) {
            throw std::invalid_argument("route or block not found");
        }
    }
}

using namespace TrackModel;

// Testing
//---------------------------------------------------------------------------------
const std::string LAYOUT_FILE = "blue_line.csv";
const std::string ROUTE_NAME = "Blue Line";

Route *initTestLayout() {
    Route *blue_line = new Route(ROUTE_NAME);

    try {
        blue_line->loadLayout(LAYOUT_FILE);
    }
    catch( const LayoutParseError &e ) {
        std::cerr << "Failed to parse layout file:" << std::endl;
        std::cerr << e.what() << std::endl;
        return NULL;
    }

    Block *first = blue_line->getBlock(1);
    blue_line->spawnBlock = first;

    routes.push_back(blue_line);
    initRouteState(blue_line);

    return blue_line;
}

int trackModelTestMain() {
    yard = new Block(0, "Yard", 0, 0, 100);

    Route *r = new Route(ROUTE_NAME);

    try {
        r->loadLayout(LAYOUT_FILE);
    }
    catch( const LayoutParseError &e ) {
        std::cerr << "Failed to parse layout file:" << std::endl;
        std::cerr << e.what() << std::endl;
        return -1;
    }

    routes.push_back(r);
    initRouteState(r);
    
    Block *block = r->getBlock(1);
    while( block != NULL ) {
        std::cout << "Block " << block->id << " sec " << block->section;
        std::cout << " grade " << (block->grade * 100) << "%";

        Switch *sw = r->getSwitch(block->id);
        if( sw != NULL ) {
            std::cout << " (branch -> " << sw->divergeBlock->id << ")";
        }

        if( block->station != NULL ) {
            std::cout << " [" << block->station->name << "]";
        }

        std::cout << std::endl;

        block = block->nextBlock;
    }

    addOccupancy(r->name, 7);

    std::cout << "Block 7 occupied: " << isBlockOccupied(r->name, 7) << std::endl;

    return 0;
}
