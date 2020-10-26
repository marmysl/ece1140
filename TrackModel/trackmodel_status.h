#pragma once

#include "tracklayout.hpp"

namespace TrackModel
{
    struct BlockStatus
    {
    public:
        Block *layoutBlock;
        int trainCount;
        BlockFault faults;

        BlockStatus( Block *block ) : layoutBlock(block), trainCount(0), faults(FAULT_NONE), circuit(TrackCircuitData()) {}

        TrackCircuitData getCircuitData()
        {
            if( isFaultSet(faults, FAULT_CIRCUIT_FAIL) ) return TrackCircuitData(0);
            else return circuit;
        }

        void setCircuitData( const TrackCircuitData &data )
        {
            circuit = data;
        }

        bool isOccupied() {
            return trainCount > 0;
        }

        inline int id() {
            return layoutBlock->id;
        }

    private:
        TrackCircuitData circuit;
    };

    struct StationStatus
    {
        Station *layoutStation;
        int numPassengers;

        StationStatus( Station *station ) : layoutStation(station), numPassengers(0) {}

        inline QString name() {
            return QString::fromStdString(layoutStation->name);
        }
    };

    struct RouteStatus
    {
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
                return nullptr;
            }
        }

        StationStatus *getStationStatus( std::string name )
        {
            for( StationStatus *&s : stationList )
            {
                if( !name.compare(s->layoutStation->name) ) return s;
            }
            return nullptr;
        }
    };
}
