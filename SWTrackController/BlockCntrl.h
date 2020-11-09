//This file contains a class declaration
#ifndef BlockCntrl_h
#define BlockCntrl_h

#include <cstdint>
#include <string>

class BlockCntrl
{
	private:
		
		char section; 
	
	public:

        int block_num; //change to block_id
        std::string line;
        bool block_occ;
        bool switch_head;
        bool switch_tail;
        bool switch_state;
        int lights[2]; //change to light_state
        bool cross_state;
        uint32_t block_speed;
        uint32_t block_authority;
        bool block_fail;
        BlockCntrl();
        void setUpBlock(std::string &, int);
        void setCircuit();
        void setSpdAuth(float, int);
        void setOcc();
        void getOcc();
        void setSwitch(int,bool);
        void getFailures();


		int getRes();



};

#endif /*BlockCntrl_h*/
