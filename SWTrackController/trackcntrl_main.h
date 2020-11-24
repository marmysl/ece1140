#ifndef TRACKCNTRL_MAIN_H
#define TRACKCNTRL_MAIN_H

#include "waysidecontainer.h"
#include "tracklogic.h"
#include "CTCSignals.h"
#include "swtrackcntrlwindow.h"

#include <vector>
#include <string>
#include <iostream>


extern QMainWindow *programmerGUI;


void alertWaysideSystem(std::string &, CTCSignals &);

TrackController getWaysideInstance(int);

void setPLCFile(std::string &);

void setSwitchUI(TrackController &, bool);

void setCrossingUI(TrackController &, bool);

void timerEvent(QTimerEvent *event);

void updateWaysides();

int init_SWTrackController();







#endif // TRACKCNTRL_MAIN_H
