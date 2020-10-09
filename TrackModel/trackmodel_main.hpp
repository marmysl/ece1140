#pragma once

#include <string>
#include <vector>
#include "tracklayout.hpp"

namespace TrackModel {
    struct RouteFile {
        std::string name;
        std::string layoutFile;

        RouteFile( std::string name, std::string file ) :
            name(name), layoutFile(file) {}
    };

    extern std::vector<RouteFile> routesToLoad;

    int loadLayouts();
}
