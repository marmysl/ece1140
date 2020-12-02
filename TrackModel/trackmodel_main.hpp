#pragma once

#include <string>
#include <vector>
#include "tracklayout.hpp"
#include "trackmodeldisplay.h"
#include "trackmodel_status.h"

namespace TrackModel {
    struct RouteFile {
        QString name;
        QString layoutFile;

        RouteFile( QString name, QString file ) :
            name(name), layoutFile(file) {}
    };

    extern TrackModelDisplay *trackModelUi;
    extern std::vector<RouteFile> routesToLoad;

    void changeLayouts();
    int initializeTrackModel();
    RouteStatus *getRouteStatus( QString name );
}
