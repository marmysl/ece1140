#include "trackcntrl_main.h"

CTCSignals ctc_track_controller;

WaysideContainer wayside_vector;

int init_SWTrackController() {
    //int timerID = startTimer(1000); // timer event occurs every second
    //int count = 0;


    std::vector<char> s;
    s.push_back('A');
    s.push_back('B');
    s.push_back('C');

    std::vector<int> b;
    for(int i = 1; i <= 15; i++) {
        b.push_back(i);     }

    std::string track_line = "Blue Line";

    wayside_vector.addTrackObj(1, track_line, s, b);
    //wayside_vector.addCTCObj(ctc_track_controller);


	return 0;
}

void alertWaysideSystem(CTCSignals &temp) {

    wayside_vector.addCTCObj(temp);
    //std::cout << "\n\nspeed: " << temp.speedCTC << ", authority: " << temp.authCTC << "\n\n";
}
