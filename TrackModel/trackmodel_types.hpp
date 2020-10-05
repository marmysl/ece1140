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

    struct TrackCircuit {
        uint16_t speed;
        uint16_t authority;
    };

    struct Transponder {
        uint8_t data[64];
    };
}