#include <iostream>
#include <unordered_map>
#include "tracklayout.hpp"
#include "trackmodel_main.hpp"
#include "ui_trackmodeldisplay.h"

namespace TrackModel {
    // extern
    TrackModelDisplay *trackModelUi = NULL;
    std::vector<RouteFile> routesToLoad;

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
        RouteStatus *rs = new RouteStatus(route);
        routeStatusMap[route->name] = rs;
        
        for( auto kvp : route->blocks ) {
            rs->addBlock(kvp.second);
        }
    }

    // apply the given fault to this block
    // returns: the new fault state
    BlockFault setFault( std::string route, int block, BlockFault fault ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->getBlockStatus(block);

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
            BlockStatus *blockInfo = routeInfo->getBlockStatus(block);

            blockInfo->faults = blockInfo->faults & ~fault;
            return blockInfo->faults;
        }
        catch( const std::out_of_range &e ) {
            throw std::invalid_argument("route or block not found");
        }
    }

    RouteStatus *getRouteStatus( QString name )
    {
        try
        {
            return routeStatusMap.at(name.toStdString());
        }
        catch( const std::out_of_range &e )
        {
            return NULL;
        }
    }

    // load and initialize all layout files in routesToLoad
    // returns: 0 on success, negative number on error
    int loadLayouts() {
        routes.clear();

        for( RouteFile rf : routesToLoad ) {
            Route *blue_line = new Route(rf.name);

            try {
                blue_line->loadLayout(rf.layoutFile);
            }
            catch( const LayoutParseError &e ) {
                std::cerr << "Failed to parse layout file:" << std::endl;
                std::cerr << e.what() << std::endl;
                return -1;
            }

            Block *first = blue_line->getBlock(1);
            blue_line->spawnBlock = first;

            routes.push_back(blue_line);
            initRouteState(blue_line);
        }

        if( trackModelUi == NULL ) {
            // Instantiate the UI singleton
            trackModelUi = new TrackModelDisplay();
            trackModelUi->show();
        }

        trackModelUi->setRegionList(&routes);

        return 0;
    }
}
