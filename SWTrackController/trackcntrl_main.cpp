#include "waysidecontainer.h"
#include "tracklogic.h"
#include "CTCOffice/ctcoffice/CTCSignals.h"
#include "../TrackModel/trackmodel_controller.hpp"
#include "../TrackModel/trackmodel_main.hpp"
#include <vector>
#include <iostream>

void timerEvent(QTimerEvent *event);

int init_SWTrackController() {
    //int timerID = startTimer(1000); // timer event occurs every second
    //int count = 0;

    CTCSignals C1;

    WaysideContainer wayside_vector;

    std::vector<char> s;
    s.push_back('A');
    s.push_back('B');
    s.push_back('C');

    std::vector<int> b;
    for(int i = 1; i <= 15; i++) {
        b.push_back(i);     }

    wayside_vector.addTrackObj(1, s, b);
	
    //timer implementation



    wayside_vector.blocks.begin() -> setSpdAuth(1, C1.speedCTC, C1.authCTC);

    std::string route = "Blue";

    TrackModel::TrackCircuitData block1 = TrackModel::TrackCircuitData::fromFloat(30,500);
    TrackModel::setTrackCircuit(route, 1, block1);

    TrackModel::TrackCircuitData block2 = TrackModel::TrackCircuitData::fromFloat(30,450);
    TrackModel::setTrackCircuit(route, 2, block2);

    TrackModel::TrackCircuitData block3 = TrackModel::TrackCircuitData::fromFloat(30,400);
    TrackModel::setTrackCircuit(route, 3, block3);

    TrackModel::TrackCircuitData block4 = TrackModel::TrackCircuitData::fromFloat(30,350);
    TrackModel::setTrackCircuit(route, 4, block4);

    TrackModel::TrackCircuitData block5 = TrackModel::TrackCircuitData::fromFloat(30,300);
    TrackModel::setTrackCircuit(route, 5, block5);

    TrackModel::TrackCircuitData block6 = TrackModel::TrackCircuitData::fromFloat(30,250);
    TrackModel::setTrackCircuit(route, 6, block6);

    TrackModel::TrackCircuitData block7 = TrackModel::TrackCircuitData::fromFloat(30,200);
    TrackModel::setTrackCircuit(route, 7, block7);

    TrackModel::TrackCircuitData block8 = TrackModel::TrackCircuitData::fromFloat(20,150);
    TrackModel::setTrackCircuit(route, 8, block8);

    TrackModel::TrackCircuitData block9 = TrackModel::TrackCircuitData::fromFloat(20,100);
    TrackModel::setTrackCircuit(route, 9, block9);

    TrackModel::TrackCircuitData block10 = TrackModel::TrackCircuitData::fromFloat(10,50);
    TrackModel::setTrackCircuit(route, 10, block10);

    TrackModel::TrackCircuitData block11 = TrackModel::TrackCircuitData::fromFloat(30,250);
    TrackModel::setTrackCircuit(route, 11, block11);

    TrackModel::TrackCircuitData block12 = TrackModel::TrackCircuitData::fromFloat(30,200);
    TrackModel::setTrackCircuit(route, 12, block12);

    TrackModel::TrackCircuitData block13 = TrackModel::TrackCircuitData::fromFloat(30,150);
    TrackModel::setTrackCircuit(route, 13, block13);

    TrackModel::TrackCircuitData block14 = TrackModel::TrackCircuitData::fromFloat(30,100);
    TrackModel::setTrackCircuit(route, 14, block14);

    TrackModel::TrackCircuitData block15 = TrackModel::TrackCircuitData::fromFloat(30,50);
    TrackModel::setTrackCircuit(route, 15, block15);


    for (auto i = wayside_vector.blocks.begin(); i != wayside_vector.blocks.end(); ++i) {
        i -> setOcc();    }


	return 0;
}

