#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "trackmodel_types.hpp"

namespace TrackModel {
    class Route;
    class Block;
    class Station;
    class Switch;
    class Linkable;

    extern std::vector<Route *> routes;

    // Get the route with the given name
    Route *getRoute( std::string name );

    class LayoutParseError : public std::runtime_error {
        public:
            LayoutParseError( std::string msg ) : std::runtime_error(msg) {}
    };

    // Represents a route/line (eg green line, red line)
    class Route {
        public:
            std::unordered_map<int, Block*> blocks;
            std::unordered_map<int, Switch*> switches;
            std::vector<Station *> stations;

            std::string name;

            Block *spawnBlock;
            BlockDir spawnDir;

            int displayStartBlk;
            BlockDir displayStartDir;

            Route( std::string name );

            // Initialize track layout from CSV file
            void loadLayout( std::string fileName );

            // get the block with the given id
            Block *getBlock( int blockId );

            // get the switch attached to the given block id
            Switch *getSwitch( int fromBlockId );

            // get the station with the given name
            Station *getStationByName( std::string stationName );
    };

    class Linkable
    {
    public:
        virtual Block *getTarget() = 0;
        virtual bool hasTarget( Block *tgt ) = 0;
    };

    struct NextBlockData
    {
        Block *block;
        BlockDir entryDir;
    };

    inline bool operator==( const NextBlockData &a, const NextBlockData &b )
    {
        return (a.block == b.block) && (a.entryDir == b.entryDir);
    }

    struct PlatformData
    {
        Station *station;
        PlatformSide side;

        PlatformData() : station(nullptr), side(PS_NONE) {}

        inline bool exists() { return (station != nullptr); }
    };

    class Block : public Linkable {
        public:
            int id;
            std::string section;
            float length;
            float grade;
            float speedLimit;

            BlockDir oneWay;
            PlatformData platform;
            bool underground;
            bool crossing;

            Linkable *reverseLink;
            Linkable *forwardLink;

            Block( int id, std::string section, float length, float grade, float speedLimit, BlockDir oneWay = BLK_NODIR, bool tunnel = false, bool cross = false );

            /*! Connect this block to another block in the given direction */
            void setLink( BlockDir direction, Linkable *newBlock );
            /*! Get the outgoing link (Block/Switch) in the given direction */
            Linkable *getLink( BlockDir direction );

            /*! Find the next block in the given travel direction (relative to this block) */
            NextBlockData getNextBlock( BlockDir direction );
            /*! Find the entry direction into the given neighbor coming from this block */
            BlockDir getEntryDir( Block *neighbor );

            /*! Determine if this block is traversable in the given direction */
            bool canTravelInDir( BlockDir direction );

            /*! Get info about the platform in the given travel direction */
            PlatformData getPlatformInDir( BlockDir dir );

            // Linkable interface
            Block *getTarget();
            bool hasTarget( Block *tgt );
    };

    class Switch : public Linkable {
        public:
            Block *fromBlock;
            BlockDir fromBlockDir;

            Block *straightBlock;
            Block *divergeBlock;

            SwitchState direction;

            Switch( Block *from, BlockDir fromDir, Block *straight, Block *diverge);

            // move the points of this switch to the given direction, and update block connections
            // returns: the new state of the switch
            void setDirection( SwitchState newState );

            // Linkable interface
            Block *getTarget();
            bool hasTarget( Block *tgt );
    };

    class Station {
        public:
            std::string name;
            std::vector<Block *> attachedBlocks;

            Station( std::string name );
    };
}
