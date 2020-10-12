#pragma once

#include <string>
#include "trackmodel_types.hpp"

namespace TrackModel {
    // get the track circuit data for a certain block
    TrackCircuitData getTrackCircuit( std::string route, int blockId );

    // add a train presence to indicated block
    void addOccupancy( std::string route, int blockId );

    // remove a train presence from the indicated block
    void removeOccupancy( std::string route, int blockId );

    // remove up to the given # of passengers from a station
    // returns: actual number of passengers moved
    int takePassengers( std::string route, std::string station, int maxTransfer );
}
