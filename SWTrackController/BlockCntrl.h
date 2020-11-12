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

        int block_num;
        std::string line;
        bool block_occ;
        bool switch_head;
        bool switch_tail;
        bool active_tail;
        bool switch_state;
        int lights[2];
        bool cross_block;
        bool cross_state;
        float block_speed;
        int block_authority;
        bool block_fail;
        bool default_last_block;
        bool active_last_block;

        BlockCntrl();
        void setUpBlock(std::string &, int, int[4], int, int, int);
        void setCircuit();
        void setSpdAuth(float, int);
        void setOcc();
        void getOcc();
        void setSwitch(int,bool);
        void getFailures();

        //PLC variables
        bool current_occ;
        bool next_occ;
        bool plc_speed;
        bool speed_safe;
        bool sw_state;
        bool crossing_state;
        bool light_state[2];
        bool plc_auth;
        bool auth_safe;

		int getRes();



};

#endif /*BlockCntrl_h*/
