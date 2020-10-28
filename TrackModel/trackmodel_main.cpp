#include <iostream>
#include <unordered_map>
#include "tracklayout.hpp"
#include "trackmodel_main.hpp"
#include "layoutdialog.h"
#include "trackmodeldisplay.h"

#include <QDebug>

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
            blockInfo->setCircuitData(data);

            trackModelUi->notifyBlockUpdated(routeInfo, blockId);
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

    SwitchState getSwitchState( std::string route, int switchBlockId )
    {
        Route *routeObj = getRoute(route);
        Switch *s = routeObj->getSwitch(switchBlockId);

        if( s == NULL ) throw std::invalid_argument("Requested switch not found");
        return s->direction;
    }

    void setSwitchState( std::string route, int switchBlockId, SwitchState newDirection )
    {
        Route *routeObj = getRoute(route);
        Switch *s = routeObj->getSwitch(switchBlockId);

        if( s == NULL ) throw std::invalid_argument("Requested switch not found");
        s->setDirection(newDirection);

        trackModelUi->notifySwitchUpdated(routeObj, switchBlockId);
    }

    void setSignal( std::string route, int blockId, BlockDir direction, SignalState newState )
    {
        if( direction == BLK_NODIR ) return;

        try
        {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(blockId);

            if( direction == BLK_FORWARD ) blockInfo->fSignal = newState;
            else blockInfo->rSignal = newState;

            trackModelUi->notifyBlockUpdated(routeInfo, blockId);
        }
        catch( const std::out_of_range &e )
        {
            throw std::invalid_argument("route or block not found");
        }
    }


    // Train Model Interface
    //---------------------------------------------------------------------------------
    TrackCircuitData getTrackCircuit( std::string route, int blockId ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->blockMap.at(blockId);
            return blockInfo->getCircuitData();
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

            trackModelUi->notifyBlockUpdated(routeInfo, blockId);
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

    int takePassengers( std::string route, std::string station, int maxTransfer )
    {
        try
        {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            StationStatus *stationInfo = routeInfo->getStationStatus(station);

            int nTrans = std::min(stationInfo->numPassengers, maxTransfer);
            stationInfo->numPassengers -= nTrans;

            trackModelUi->notifyStationUpdated(routeInfo->layoutRoute, station);

            return nTrans;
        }
        catch( const std::out_of_range &e )
        {
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

        for( Station *&s : route->stations ) {
            rs->addStation(s);
        }
    }

    // apply the given fault to this block
    // returns: the new fault state
    BlockFault setFault( std::string route, int block, BlockFault fault ) {
        try {
            RouteStatus *routeInfo = routeStatusMap.at(route);
            BlockStatus *blockInfo = routeInfo->getBlockStatus(block);

            blockInfo->faults = blockInfo->faults | fault;
            trackModelUi->notifyBlockUpdated(routeInfo, block);

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
            trackModelUi->notifyBlockUpdated(routeInfo, block);

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
    int initializeTrackModel()
    {
        routes.clear();

        LayoutDialog diag;
        diag.exec();

        for( RouteFile rf : routesToLoad ) {
            Route *newRoute = new Route(rf.name.toStdString());

            try {
                newRoute->loadLayout(rf.layoutFile.toStdString());
            }
            catch( const LayoutParseError &e ) {
                qDebug() << "Failed to parse layout file:\n";
                qDebug() << e.what() << '\n';
                return -1;
            }

            Block *first = newRoute->getBlock(1);
            newRoute->spawnBlock = first;

            routes.push_back(newRoute);
            initRouteState(newRoute);
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
