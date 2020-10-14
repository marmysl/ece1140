#pragma once

#include <string>
#include <vector>
#include "tracklayout.hpp"
#include "trackmodeldisplay.h"

namespace TrackModel {
    struct BlockStatus {
        Block *layoutBlock;

        TrackCircuitData circuit;
        int trainCount;
        BlockFault faults;

        BlockStatus( Block *block ) : layoutBlock(block), circuit(TrackCircuitData()), trainCount(0), faults(FAULT_NONE) {}

        bool isOccupied() {
            return trainCount > 0;
        }

        inline int id() {
            return layoutBlock->id;
        }
    };

    struct StationStatus {
        Station *layoutStation;
        int numPassengers;

        StationStatus( Station *station ) : layoutStation(station), numPassengers(0) {}

        inline QString name() {
            return QString::fromStdString(layoutStation->name);
        }
    };

    struct RouteStatus {
        Route *layoutRoute;
        std::unordered_map<int, BlockStatus *> blockMap;
        std::vector<StationStatus *> stationList;

        RouteStatus( Route *r ) : layoutRoute(r) {}

        void addBlock( Block *b )
        {
            blockMap[b->id] = new BlockStatus(b);
        }

        void addStation( Station *s )
        {
            stationList.push_back(new StationStatus(s));
        }

        BlockStatus *getBlockStatus( int blockId )
        {
            try
            {
                return blockMap.at(blockId);
            }
            catch( const std::out_of_range &e )
            {
                return NULL;
            }
        }

        StationStatus *getStationStatus( std::string name )
        {
            for( StationStatus *&s : stationList )
            {
                if( !name.compare(s->layoutStation->name) ) return s;
            }
            return NULL;
        }
    };

    struct RouteFile {
        std::string name;
        std::string layoutFile;

        RouteFile( std::string name, std::string file ) :
            name(name), layoutFile(file) {}
    };

    extern TrackModelDisplay *trackModelUi;
    extern std::vector<RouteFile> routesToLoad;

    int initializeTrackModel();
    RouteStatus *getRouteStatus( QString name );
}
