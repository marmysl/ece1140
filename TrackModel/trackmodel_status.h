#pragma once

#include "tracklayout.hpp"
#include <QObject>

namespace TrackModel
{
    class BlockStatus : public QObject
    {
        Q_OBJECT

    public:
        Block *layoutBlock;

        BlockStatus( Block *block ) : layoutBlock(block),
            circuit(TrackCircuitData()), faults(FAULT_NONE), trainCount(0),
            rSignal(TSIG_RED), fSignal(TSIG_RED) {}

        TrackCircuitData getCircuitData() const;
        void setCircuitData( const TrackCircuitData &data );

        BlockFault getFaults() const;
        void setFaults( BlockFault newFaults );
        void addFault( BlockFault newFault );
        void clearFault( BlockFault toClear );

        void incTrainCount();
        void decTrainCount();

        SignalState getSignal( BlockDir dir );
        void setSignal( BlockDir dir, SignalState state );

        void setCrossingState(bool);
        bool getCrossingState() { return crossingActive; }

        bool isOccupied() {
            return trainCount > 0;
        }

        int id() {
            return layoutBlock->id;
        }

    private:
        TrackCircuitData circuit;
        BlockFault faults;
        int trainCount;
        SignalState rSignal;
        SignalState fSignal;
        bool crossingActive;

    signals:
        void dataChanged( int senderId );
    };


    // StationStatus
    //------------------------------------------------------------------------------------
    class StationStatus : public QObject
    {
        Q_OBJECT

    public:
        Station *layoutStation;
        int numPassengers;

        StationStatus( Station *station ) : layoutStation(station), numPassengers(0) {}

        inline QString name() {
            return QString::fromStdString(layoutStation->name);
        }

    signals:
        void dataChanged( const QString &name );
    };


    // RouteStatus
    //------------------------------------------------------------------------------------
    class RouteStatus : public QObject
    {
        Q_OBJECT

    public:
        Route *layoutRoute;
        std::unordered_map<int, BlockStatus *> blockMap;
        std::vector<StationStatus *> stationList;

        RouteStatus( Route *r ) : layoutRoute(r) {}

        void addBlock( Block *b );

        void addStation( Station *s )
        {
            stationList.push_back(new StationStatus(s));
        }

        BlockStatus *getBlockStatus( int blockId )
        {
            try
            {
                return blockMap.at(blockId);
            }
            catch( const std::out_of_range &e )
            {
                return nullptr;
            }
        }

        StationStatus *getStationStatus( std::string name )
        {
            for( StationStatus *&s : stationList )
            {
                if( !name.compare(s->layoutStation->name) ) return s;
            }
            return nullptr;
        }

    public slots:
        void on_blockUpdated( int blockId );

    signals:
        void blockUpdated( RouteStatus *sender, int blockId );
    };
}
