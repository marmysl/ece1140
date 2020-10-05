#pragma once

#include <stdint.h>

namespace TrackModel {
    enum BlockDir {
        BLK_FORWARD,
        BLK_REVERSE
    };

    enum SwitchState {
        SW_STRAIGHT,
        SW_DIVERGING
    };

    enum BlockFault {
        FAULT_NONE = 0,
        FAULT_BROKEN_RAIL = 1,
        FAULT_CIRCUIT_FAIL = 2,
        FAULT_POWER_FAIL = 4
    };

    inline BlockFault operator|( BlockFault a, BlockFault b ) {
        return static_cast<BlockFault>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline BlockFault operator&( BlockFault a, BlockFault b ) {
        return static_cast<BlockFault>(static_cast<int>(a) & static_cast<int>(b));
    }

    inline BlockFault operator~( BlockFault a ) {
        return static_cast<BlockFault>(~static_cast<int>(a));
    }

    inline bool isFaultSet( BlockFault faults, BlockFault flag ) {
        return (faults & flag) != FAULT_NONE;
    }

    struct TrackCircuitData {
        uint32_t speed;
        uint32_t authority;

        TrackCircuitData( uint32_t speed, uint32_t auth ) :
            speed(speed), authority(auth) {}

        TrackCircuitData( float speedKph, float authKm ) {
            speed = (uint32_t)(speedKph * 4096);
            authority = (uint32_t)(authKm * 4096);
        }

        float decodeSpeed() {
            return ((float)speed) / 4096;
        }

        float decodeAuthority() {
            return ((float)authority) / 4096;
        }
    };

    struct Transponder {
        uint8_t data[64];
    };
}