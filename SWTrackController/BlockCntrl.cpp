//This file contains the definitions of the member functions.
#include <iostream>
#include <vector>
#include "BlockCntrl.h"
#include "TrackModel/trackmodel_controller.hpp"

BlockCntrl::BlockCntrl() {
    block_fail = 0;
	
}

void BlockCntrl::setUpBlock(std::string &l, int block, int switch_id[], int crossing_id) {
	block_num = block;
    line = l;

    if (block_num == switch_id[0]) {
        switch_head = true;
        switch_tail = false;
        active_tail = false;
    }
    else if (block_num == switch_id[1]) {
        switch_head = false;
        switch_tail = true;
        active_tail = true;
    }
    else if (block_num == switch_id[2]) {
        switch_head = false;
        switch_tail = true;
        active_tail = false;
    }
    else {
        switch_head = false;
        switch_tail = false;
        active_tail = false;
    }
		
	
    if (crossing_id == block_num) {
        cross_block = true;
        cross_state = false;
    }
	
		
}

int BlockCntrl::getRes() {
	
    std::cout << "section: " << section << "block: " << block_num << "switch_head: " << switch_head << "switch_tail: " << switch_tail << "\n\n";
	
    return 0;
}

void BlockCntrl::setCircuit() {

    TrackModel::TrackCircuitData data = TrackModel::TrackCircuitData::fromFloat(com_block_speed, com_block_authority);
	
    TrackModel::setTrackCircuit(line, block_num, data);
	
}

void BlockCntrl::setOcc() {

    block_occ = TrackModel::isBlockOccupied(line, block_num);
    current_occ = block_occ;

    if (current_occ == true) {
        if (cross_block == true) {
            cross_state = true;
        }
        else {
            cross_state = false;
        }
    }
    else {
        cross_state = false;
    }

}

void BlockCntrl::setSpdAuth(float s, int a) {
    sug_block_speed = s;
    sug_block_authority = a;


    if (sug_block_speed > 0) {
        plc_speed = true;
    }
    else {
        plc_speed = false;
    }
    if (sug_block_authority > 0) {
        plc_auth = true;
    }
    else {
        plc_auth = false;
    }

	
}





