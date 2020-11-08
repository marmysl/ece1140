#ifndef TRACKCNTRL_MAIN_H
#define TRACKCNTRL_MAIN_H

#include "waysidecontainer.h"
#include "tracklogic.h"
#include "CTCOffice/ctcoffice/CTCSignals.h"
#include "../TrackModel/trackmodel_controller.hpp"
#include "../TrackModel/trackmodel_main.hpp"
#include "../TrackModel/tracklayout.hpp"

#include <vector>
#include <iostream>


extern CTCSignals ctc_track_controller;


void timerEvent(QTimerEvent *event);


int init_SWTrackController();







#endif // TRACKCNTRL_MAIN_H
