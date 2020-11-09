//This file contains the definitions of the member functions.
#include <iostream>
#include <vector>
#include "BlockCntrl.h"
#include "TrackModel/trackmodel_controller.hpp"

BlockCntrl::BlockCntrl() {
	
	
}

void BlockCntrl::setUpBlock(std::string &l, int block) {
	block_num = block;
    line = l;

    if (block_num <= 15)
		section = 'A';
	else if (block_num <= 10) 
		section = 'B';
	else
		section = 'C';
		
	
	switch_head = false;
	switch_tail = false;
	
    /*for ( auto i = cntrl_switches.begin(); i != cntrl_switches.end(); ++i)
        if (*i == block_num) {
			
			if (*i == cntrl_switches[0]) 
				switch_head = true;
				
			else
				switch_tail = true;
				
        }*/
		
}

int BlockCntrl::getRes() {
	
    std::cout << "section: " << section << "block: " << block_num << "switch_head: " << switch_head << "switch_tail: " << switch_tail << "\n\n";
	
    return 0;
}

void BlockCntrl::setCircuit() {

    if (block_num == 15 || block_num == 10) {
        block_speed = 0;
        block_authority = 0;
    }
    else {
        block_speed = 40;
    }
    if (block_num < 10) {
        block_authority = 10 - block_num - 1;
    }
    if (block_num >10) {
        block_authority = 15 - block_num - 1;
    }

    TrackModel::TrackCircuitData data = TrackModel::TrackCircuitData::fromFloat(block_speed, block_authority);
	
    TrackModel::setTrackCircuit(line, block_num, data);
	std::cout << "Block: " << block_num << "        Speed: " << block_speed << "        Authority: " << block_authority << "\n";
		
	
}

void BlockCntrl::setOcc() {
	std::string r = "Blue Line";
	
	block_occ = TrackModel::isBlockOccupied(r, block_num); 
}

void BlockCntrl::setSpdAuth(float s, int a) {
	block_speed = s;
	block_authority = a;
		
    setCircuit();
	
}




