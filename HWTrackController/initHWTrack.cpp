#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdint>

#include "HWTrackController.hpp"
#include "HWTrackController_main.h"

using namespace std;

Region reg;

void initializeHW(CTCSignals &c){
    reg.initialize(c.getExit(),c.getSpeed(),c.getAuth());
}

int init_HWTrackController() {
    HWTrackController obj;
	return 0;
}

