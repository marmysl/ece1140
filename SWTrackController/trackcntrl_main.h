#ifndef TRACKCNTRL_MAIN_H
#define TRACKCNTRL_MAIN_H

#include "waysidecontainer.h"
#include "tracklogic.h"
#include "CTCSignals.h"
#include "swtrackcntrlwindow.h"
#include "../TrackModel/trackmodel_controller.hpp"
#include "../TrackModel/trackmodel_main.hpp"
#include "../TrackModel/tracklayout.hpp"

#include <vector>
#include <string>
#include <iostream>


extern QMainWindow *programmerGUI;

//extern WaysideContainer *blue;
//extern WaysideContainer *green;
//extern WaysideContainer *red;

void alertWaysideSystem(std::string &, CTCSignals &);

TrackController getWaysideInstance(int);

void setPLCFile(std::string &);

void setSwitchUI(TrackController &, bool);

void timerEvent(QTimerEvent *event);


int init_SWTrackController();







#endif // TRACKCNTRL_MAIN_H
