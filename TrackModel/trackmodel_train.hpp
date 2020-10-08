#pragma once

#include <string>
#include "trackmodel_types.hpp"

namespace TrackModel {
    TrackCircuitData getTrackCircuit( std::string route, int blockId );

    // add a train presence to indicated block
    void addOccupancy( std::string route, int blockId );

    // remove a train presence from the indicated block
    void removeOccupancy( std::string route, int blockId );
}
