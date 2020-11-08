#include "CTCBlockStatus.h"

// CTCBlockStatus
TrackCircuitData CTCBlockStatus::getCircuitData() const
{
    if( isFaultSet(faults, FAULT_CIRCUIT_FAIL) ) return TrackCircuitData(0);
    else return circuit;
}

void CTCBlockStatus::setCircuitData( const TrackCircuitData &data )
{
    if( data != circuit )
    {
        circuit = data;
    }
}

BlockFault CTCBlockStatus::getFaults() const
{
    return faults;
}

void CTCBlockStatus::setFaults( BlockFault newFaults )
{
    if( newFaults != faults )
    {
        faults = newFaults;
    }
}

void CTCBlockStatus::addFault( BlockFault newFault )
{
    if( !isFaultSet(faults, newFault) )
    {
        faults |= newFault;
    }
}

void CTCBlockStatus::clearFault( BlockFault toClear )
{
    BlockFault result = faults & (~toClear);
    if( result != faults )
    {
        faults = result;
    }
}

void CTCBlockStatus::setOcc(bool o)
{
    occ = o;
}

SignalState CTCBlockStatus::getSignal( BlockDir dir )
{
    if( dir == BLK_FORWARD ) return fSignal;
    else return rSignal;
}

void CTCBlockStatus::setSignal( BlockDir dir, SignalState state )
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

}


// RouteStatus
void CTCRouteStatus::addBlock( Block *b )
{
    CTCBlockStatus *newBlk = new CTCBlockStatus(b);
    blockMap[b->id] = newBlk;
}

