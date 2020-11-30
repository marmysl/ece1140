#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdint>

#include "HWTrackController.hpp"
#include "HWTrackController_main.h"
#include "hwplcui.h"

using namespace std;

Region reg;

int init_HWTrackController() {
    HWTrackController* obj = new HWTrackController();
    HWPLCUI *w = new HWPLCUI();
    w->show();
	return 0;
}

