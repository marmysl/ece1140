#pragma once

#include "trackmodel_types.hpp"

namespace TrackModel {
    // update speed/authority signal to a block
    void setTrackCircuit( std::string route, int blockId, TrackCircuitData data );

    // check whether the given block contains >= 1 train
    bool isBlockOccupied( std::string route, int blockId );

    // get the current fault flags for the given block
    BlockFault getFaults( std::string route, int blockId );

    // check the current direction of the switch attached to the given block
    SwitchState getSwitchState( std::string route, int switchBlockId );

    // change the direction of the switch attached to the given block
    void setSwitchState( std::string route, int switchBlockId, SwitchState newDirection );
}