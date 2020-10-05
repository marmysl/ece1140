#pragma once

#include "trackmodel_types.hpp"

namespace TrackModel {
    // update speed/authority signal to a block
    void setTrackCircuit( int blockId, TrackCircuitData data );

    // check whether the given block contains >= 1 train
    bool isBlockOccupied( int blockId );

    // get the current fault flags for the given block
    BlockFault getFaults( int blockId );

    // check the current direction of the switch attached to the given block
    SwitchState getSwitchState( int switchBlockId );

    // change the direction of the switch attached to the given block
    SwitchState setSwitchState( int switchBlockId, SwitchState newDirection );
}