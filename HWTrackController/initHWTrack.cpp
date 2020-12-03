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
bool existence = 0;

/*
* Initializes HW Track Controller golobal instances of Red and Green Line regions are made
*/
int init_HWTrackController() {
    existence = 1;  // I exist
    HWPLCUI *w = new HWPLCUI();
    w->show();
	return 0;
}

