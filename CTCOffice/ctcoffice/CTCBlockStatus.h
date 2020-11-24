#pragma once

#include "TrackModel/tracklayout.hpp"

//Train signals check = failure_code
//Switch states check = vector of pairs(blockid, switchstate)
//block occupancy check = occupancy
//faults check
//passenger count check
//stations check

using namespace TrackModel;

class CTCBlockStatus {

public:
    Block *layoutBlock;

    CTCBlockStatus( Block *block ) : layoutBlock(block), passnum(0),
        circuit(TrackCircuitData()), faults(FAULT_NONE), occ(0),
        rSignal(TSIG_RED), fSignal(TSIG_RED) {}

    TrackCircuitData getCircuitData() const;
    void setCircuitData( const TrackCircuitData &data );

    BlockFault getFaults() const;
    void setFaults( BlockFault newFaults );
    void addFault( BlockFault newFault );
    void clearFault( BlockFault toClear );

    void setOcc(bool);

    int passnum;

    SignalState getSignal( BlockDir dir );
    void setSignal( BlockDir dir, SignalState state );

    bool isOccupied() {
        return occ;
    }

    int id() {
        return layoutBlock->id;
    }

private:
    TrackCircuitData circuit;
    BlockFault faults;
    bool occ;
    SignalState rSignal;
    SignalState fSignal;

};

// RouteStatus
//------------------------------------------------------------------------------------
class CTCRouteStatus{

public:
    Route *layoutRoute;
    std::unordered_map<int, CTCBlockStatus *> blockMap;

    CTCRouteStatus( Route *r ) : layoutRoute(r) {}

    void addBlock( Block *b );

    CTCBlockStatus *getBlockStatus( int blockId )
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
};

