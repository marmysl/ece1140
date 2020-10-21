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

    extern Block *yard;

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
    };

    class Block : public Linkable {
        public:
            int id;
            std::string section;
            float length;
            float grade;
            float speedLimit;

            BlockDir oneWay;
            Station *station;

            Linkable *prevBlock;
            Linkable *nextBlock;

            Block( int id, std::string section, float length, float grade, float speedLimit, BlockDir oneWay = BLK_NODIR );

            // connect this block to another block in the given direction
            void setLink( BlockDir direction, Linkable *newBlock );
            Block *getLink( BlockDir direction );

            Block *getTarget();
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

            Block *getTarget();
    };

    class Station {
        public:
            std::string name;

            Station( std::string name );
    };
}
