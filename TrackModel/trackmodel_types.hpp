#pragma once

#include <stdint.h>
#include <sstream>
#include <QString>

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

    inline BlockFault operator|( const BlockFault &a, const BlockFault &b ) {
        return static_cast<BlockFault>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline BlockFault& operator|=( BlockFault &a, const BlockFault &b ) {
        return (a = (a | b));
    }

    inline BlockFault operator&( const BlockFault &a, const BlockFault &b ) {
        return static_cast<BlockFault>(static_cast<int>(a) & static_cast<int>(b));
    }

    inline BlockFault& operator&=( BlockFault &a, const BlockFault &b ) {
        return (a = (a & b));
    }

    inline BlockFault operator~( const BlockFault &a ) {
        return static_cast<BlockFault>(~static_cast<int>(a));
    }

    inline bool isFaultSet( const BlockFault &faults, const BlockFault &flag ) {
        return (faults & flag) != FAULT_NONE;
    }

    QString getFaultString( const BlockFault &faults );

    struct TrackCircuitData {
        uint32_t speed;
        uint32_t authority;

        TrackCircuitData() : speed(0), authority(0) {};

        TrackCircuitData( uint64_t data ) :
            speed((uint32_t)(data >> 32)), authority((uint32_t)(data & 0xFFFFFFFFul)) {}

        static TrackCircuitData fromFixed( uint32_t speed, uint32_t auth ) {
            TrackCircuitData d;
            d.speed = speed;
            d.authority = auth;
            return d;
        }

        static TrackCircuitData fromFloat( float speedKph, float authKm ) {
            TrackCircuitData d;
            d.speed = (uint32_t)(speedKph * 4096);
            d.authority = (uint32_t)(authKm * 4096);
            return d;
        }

        float decodeSpeed() {
            return ((float)speed) / 4096;
        }

        float decodeAuthority() {
            return ((float)authority) / 4096;
        }

        uint64_t getEncodedData() {
            return ((uint64_t)speed << 32) | (uint64_t)authority;
        }

        static uint64_t encodeFromFloat( float speedKph, float authKm ) {
            return fromFloat(speedKph, authKm).getEncodedData();
        }

        static uint64_t encodeFromFixed( uint32_t speed, uint32_t auth ) {
            return fromFixed(speed, auth).getEncodedData();
        }
    };

    struct Transponder {
        uint8_t data[64];
    };
}
