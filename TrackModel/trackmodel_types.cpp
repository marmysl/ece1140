#include "trackmodel_types.hpp"

namespace TrackModel
{
    std::string faultNames[]
    {
        "BRKN RAIL",
        "CIRC FAIL",
        "PWR FAIL",
    };

    std::string faultAbbrev[]
    {
        "BR", "CF", "PF"
    };

    QString getFaultString( const BlockFault &faults )
    {
        if( faults == FAULT_NONE ) return QString("None");

        std::stringstream stream;
        bool first = true;

        BlockFault test = FAULT_POWER_FAIL;
        for( int i = 2; i >= 0; i-- )
        {
            if( isFaultSet(faults, test) )
            {
                if( !first ) stream << ", ";
                first = false;
                stream << faultNames[i];
            }
            test = static_cast<BlockFault>(test >> 1);
        }

        return QString::fromStdString(stream.str());
    }

    QString getFaultAbbrev( const BlockFault &faults )
    {
        if( faults == FAULT_NONE ) return QString();

        std::stringstream stream;
        bool first = true;

        BlockFault test = FAULT_POWER_FAIL;
        for( int i = 2; i >= 0; i-- )
        {
            if( isFaultSet(faults, test) )
            {
                if( !first ) stream << '|';
                first = false;
                stream << faultAbbrev[i];
            }
            test = static_cast<BlockFault>(test >> 1);
        }

        return QString::fromStdString(stream.str());
    }
}
