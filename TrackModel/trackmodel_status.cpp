#include "trackmodel_status.h"

namespace TrackModel {

// BlockStatus
TrackCircuitData BlockStatus::getCircuitData() const
{
    if( isFaultSet(faults, FAULT_CIRCUIT_FAIL) ) return TrackCircuitData(0);
    else return circuit;
}

void BlockStatus::setCircuitData( const TrackCircuitData &data )
{
    if( data != circuit )
    {
        circuit = data;
        emit dataChanged(id());
    }
}

BlockFault BlockStatus::getFaults() const
{
    return faults;
}

void BlockStatus::setFaults( BlockFault newFaults )
{
    if( newFaults != faults )
    {
        faults = newFaults;
        emit dataChanged(id());
    }
}

void BlockStatus::addFault( BlockFault newFault )
{
    if( !isFaultSet(faults, newFault) )
    {
        faults |= newFault;
        emit dataChanged(id());
    }
}

void BlockStatus::clearFault( BlockFault toClear )
{
    BlockFault result = faults & (~toClear);
    if( result != faults )
    {
        faults = result;
        emit dataChanged(id());
    }
}

void BlockStatus::incTrainCount()
{
    trainCount += 1;
    emit dataChanged(id());
}

void BlockStatus::decTrainCount()
{
    if( trainCount > 0 )
    {
        trainCount -= 1;
        emit dataChanged(id());
    }
}

SignalState BlockStatus::getSignal( BlockDir dir )
{
    if( dir == BLK_FORWARD ) return fSignal;
    else return rSignal;
}

void BlockStatus::setSignal( BlockDir dir, SignalState state )
{
    bool mod = false;
    if( (dir != BLK_REVERSE) && (fSignal != state) )
    {
        fSignal = state;
        mod = true;
    }
    else if( (dir != BLK_FORWARD) && (rSignal != state) )
    {
        rSignal = state;
        mod = true;
    }

    if( mod ) emit dataChanged(id());
}


// RouteStatus
void RouteStatus::addBlock( Block *b )
{
    BlockStatus *newBlk = new BlockStatus(b);
    blockMap[b->id] = newBlk;
    connect(newBlk, &BlockStatus::dataChanged, this, &RouteStatus::on_blockUpdated);
}

void RouteStatus::on_blockUpdated( int blockId )
{
    emit blockUpdated(this, blockId);
}

}
