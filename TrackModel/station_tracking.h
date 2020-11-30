#pragma once

#include <string>

namespace TrackModel
{
    /** Get the number of passengers at the given station */
    int getPassengersWaiting(std::string route, std::string station);

    /** Add given # of passengers to a station */
    void addPassengersToStation(std::string route, std::string station, int count);
}
