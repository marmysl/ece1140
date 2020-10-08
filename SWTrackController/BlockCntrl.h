//This file contains a class declaration
#ifndef BlockCntrl_h
#define BlockCntrl_h
#include "TrackController.h"


class BlockCntrl : virtual public TrackController
{
	private:
		
		char section; 
	
	public:
	
		BlockCntrl(int);
		bool switch_head;
		bool switch_tail;
		int lights[2];
		int block_num;
		uint32_t block_speed, block_authority;
		bool block_occ;
		bool block_fail; 
		int getRes();
		void setCircuit();
		void setSpdAuth(int);
		void setOcc();
};

#endif /*BlockCntrl_h*/
