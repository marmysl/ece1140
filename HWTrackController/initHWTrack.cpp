#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdint>

#include "HWTrackController_main.h"
#include "HWTrackController.hpp"
#include "hwplcui.h"
#include "CTCOffice/ctcoffice/CTCDispatch.h"

using namespace std;

Region greenreg = Region("Green Line");
Region redreg = Region("Red Line");

int init_HWTrackController() {
    HWTrackController* obj = new HWTrackController();
    HWPLCUI *w = new HWPLCUI();
    w->show();
	return 0;
}

