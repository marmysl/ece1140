//This file contains the definitions of the member functions.
#include <iostream>
#include <vector>
#include "BlockCntrl.h"
#include "TrackModel/trackmodel_controller.hpp"

BlockCntrl::BlockCntrl() {
	
	
}

void BlockCntrl::setUpBlock(int block) {
	block_num = block;
	
	if (block_num <= section_length)
		section = 'A';
	else if (block_num <= 10) 
		section = 'B';
	else
		section = 'C';
		
	
	switch_head = false;
	switch_tail = false;
	
	for ( auto i = cntrl_switches.begin(); i != cntrl_switches.end(); ++i) 
        if (*i == block_num) {
			
			if (*i == cntrl_switches[0]) 
				switch_head = true;
				
			else
				switch_tail = true;
				
		}
		
}

int BlockCntrl::getRes() {
	
	std::cout << "region: " << region << "section: " << section << "block: " << block_num << "switch_head: " << switch_head << "switch_tail: " << switch_tail << "\n\n";
	
    return 0;
}

void BlockCntrl::setCircuit() {
	std::string r = "Blue Line";
	
	TrackModel::TrackCircuitData data = TrackModel::TrackCircuitData::fromFloat(block_speed, block_authority);
	
	TrackModel::setTrackCircuit(r, block_num, data);
	std::cout << "Block: " << block_num << "        Speed: " << block_speed << "        Authority: " << block_authority << "\n";
		
	
}

void BlockCntrl::setOcc() {
	std::string r = "Blue Line";
	
	block_occ = TrackModel::isBlockOccupied(r, block_num); 
}

void BlockCntrl::setSpdAuth(int dest_block, float s, float a) {
	block_speed = s;
	block_authority = a;
		
	if (dest_block == 10) {
		
		if (block_num <= 3) {
			lights[1] = 0;
			lights[0] = 0;
		}
		
		else if (block_num <= 7) {
			lights[1] = 0;
			lights[0] = 1;
		}
		else if (block_num > 7) {
			lights[1] = 1;
			lights[0] = 0;
		} 
		else {
			lights[1] = 1;
			lights[0] = 1;
		}
	}
	
	if (dest_block == 15) {
		if (block_num <= 5) {
			lights[1] = 0;
			lights[0] = 1;
		}
		else if (block_num <= 12) {
			lights[1] = 1;
			lights[0] = 0;
		} 
		else if (block_num <= 15) {
			lights[1] = 1;
			lights[0] = 0;
		}
		else {
			lights[1] = 1;
			lights[0] = 1;
		}
	}
	
	
}




