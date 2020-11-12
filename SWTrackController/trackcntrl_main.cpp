#include "trackcntrl_main.h"



WaysideContainer blue_wayside_vector;
WaysideContainer green_wayside_vector;
WaysideContainer red_wayside_vector;

int init_SWTrackController() {

    WaysideContainer b(1);
    WaysideContainer g(12);
    WaysideContainer r(10);

    blue_wayside_vector = b;
    green_wayside_vector = g;
    red_wayside_vector = r;

	return 0;
}

void alertWaysideSystem(std::string &dis_line, CTCSignals &temp) {

    if (dis_line == "Blue Line") {
        blue_wayside_vector.addCTCObj(temp);
    }
    if (dis_line == "Green Line") {
        green_wayside_vector.addCTCObj(temp);
    }
    if (dis_line == "Red Line") {
        red_wayside_vector.addCTCObj(temp);
    }

}
