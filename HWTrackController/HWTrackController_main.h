#ifndef HWTRACKCONTROLLER_MAIN_H
#define HWTRACKCONTROLLER_MAIN_H

#include <vector>
#include <iostream>
#include <string>
#include "../SWTrackController/CTCSignals.h"
#include "Region.hpp"

extern Region reg;

void initializeHW(CTCSignals &c);
int init_HWTrackController();

#endif // HWTRACKCONTROLLER_MAIN_H
