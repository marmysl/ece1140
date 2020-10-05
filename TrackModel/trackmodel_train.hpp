#pragma once
#include "trackmodel_types.hpp"

namespace TrackModel {
    TrackCircuit getTrackCircuit( int blockId );

    // add a train presence to indicated block
    void addOccupancy( int blockId );

    // remove a train presence from the indicated block
    void removeOccupancy( int blockId );
}
