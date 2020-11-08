#pragma once

#include <stdint.h>
#include <sstream>
#include <QString>

namespace TrackModel {
    enum BlockDir {
        BLK_NODIR = 0,
        BLK_FORWARD = 1,
        BLK_REVERSE = -1
    };

    inline BlockDir oppositeDir( const BlockDir &d ) {
        return static_cast<BlockDir>(-d);
    }

    enum SwitchState {
        SW_STRAIGHT,
        SW_DIVERGING
    };

    // Begin BlockFault
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
    QString getFaultAbbrev( const BlockFault &faults );
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // End BlockFault

    enum SignalState
    {
        TSIG_RED = 0,
        TSIG_YELLOW = 1,
        TSIG_GREEN = 2
    };

    struct TrackCircuitData {
        uint32_t speed;
        uint32_t authority;

        static uint64_t encodeFromFloat( float speedKph, float authKm ) {
            return fromFloat(speedKph, authKm).getEncodedData();
        }

        static uint64_t encodeFromFixed( uint32_t speed, uint32_t auth ) {
            return fromFixed(speed, auth).getEncodedData();
        }

        static inline uint32_t floatToFixed( float floatVal )
        {
            return static_cast<uint32_t>(floatVal * 4096);
        }

        TrackCircuitData() : speed(0), authority(0) {};

        TrackCircuitData( uint64_t data ) :
            speed(static_cast<uint32_t>(data >> 32)), authority(static_cast<uint32_t>(data & 0xFFFFFFFFul)) {}

        static TrackCircuitData fromFixed( uint32_t speed, uint32_t auth ) {
            TrackCircuitData d;
            d.speed = speed;
            d.authority = auth;
            return d;
        }

        static TrackCircuitData fromFloat( float speedKph, float authKm ) {
            TrackCircuitData d;
            d.speed = floatToFixed(speedKph);
            d.authority = floatToFixed(authKm);
            return d;
        }

        float decodeSpeed() {
            return static_cast<float>(speed) / 4096;
        }

        float decodeAuthority() {
            return static_cast<float>(authority) / 4096;
        }

        uint64_t getEncodedData() {
            return (static_cast<uint64_t>(speed) << 32) | static_cast<uint64_t>(authority);
        }

        inline bool operator==( const TrackCircuitData &other ) const
        {
            return (speed == other.speed) && (authority == other.authority);
        }

        inline bool operator!=( const TrackCircuitData &other ) const
        {
            return !(operator==(other));
        }
    };

    struct Transponder {
        uint8_t data[64];
    };

    enum PlatformSide
    {
        PS_LEFT = -1,
        PS_NONE = 0,
        PS_RIGHT = 1
    };

    inline PlatformSide oppositeSide( const PlatformSide& side )
    {
        return static_cast<PlatformSide>(-side);
    }

    inline char charForSide( const PlatformSide& side )
    {
        if( side ) return (side == PS_LEFT) ? 'L' : 'R';
        else return 'N';
    }
}
