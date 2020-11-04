#include "trackcntrl_main.h"


int init_SWTrackController() {
    //int timerID = startTimer(1000); // timer event occurs every second
    //int count = 0;



    WaysideContainer wayside_vector;

    std::vector<char> s;
    s.push_back('A');
    s.push_back('B');
    s.push_back('C');

    std::vector<int> b;
    for(int i = 1; i <= 15; i++) {
        b.push_back(i);     }

    //wayside_vector.addTrackObj(1, s, b);
	
    //timer implementation


    //CTCSignals C1 = wayside_vector.signals.begin();
   // wayside_vector.blocks.begin() -> setSpdAuth(1, C1.speedCTC, C1.authCTC);

    std::string route = "Blue";

    TrackModel::TrackCircuitData tcdata = TrackModel::TrackCircuitData::fromFloat(30,9);
    TrackModel::setTrackCircuit(route, 1, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,8);
    TrackModel::setTrackCircuit(route, 2, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,7);
    TrackModel::setTrackCircuit(route, 3, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,6);
    TrackModel::setTrackCircuit(route, 4, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,5);
    TrackModel::setTrackCircuit(route, 5, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,4);
    TrackModel::setTrackCircuit(route, 6, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,3);
    TrackModel::setTrackCircuit(route, 7, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(20,2);
    TrackModel::setTrackCircuit(route, 8, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(20,1);
    TrackModel::setTrackCircuit(route, 9, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(10,0);
    TrackModel::setTrackCircuit(route, 10, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,4);
    TrackModel::setTrackCircuit(route, 11, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,3);
    TrackModel::setTrackCircuit(route, 12, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,2);
    TrackModel::setTrackCircuit(route, 13, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,1);
    TrackModel::setTrackCircuit(route, 14, tcdata);

    tcdata = TrackModel::TrackCircuitData::fromFloat(30,0);
    TrackModel::setTrackCircuit(route, 15, tcdata);

    //TrackModel::getCircuitData();

    for (auto i = wayside_vector.blocks.begin(); i != wayside_vector.blocks.end(); ++i) {
        i -> setOcc();    }


	return 0;
}

