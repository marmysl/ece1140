#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdint>

#include <QTimer>

#include "HWTrackController_main.h"
#include "hwplcui.h"
#include "CTCOffice/ctcoffice/CTCDispatch.h"

using namespace std;

Region greenreg("Green Line");
Region redreg("Red Line");

int init_HWTrackController() {
    HWPLCUI *w = new HWPLCUI();
    w->show();
	return 0;
}

