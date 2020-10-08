#include "BlockCntrl.cpp"
#include "CTCSignals.cpp"


int main() {
	
	BlockCntrl block1(1);
	std::vector<BlockCntrl> blocks;
	blocks.reserve(block1.block_count);
	blocks.push_back(block1);
	
	for (unsigned int i = 2; i < block1.block_count; ++i)
		blocks.push_back(BlockCntrl(i));
	
	CTCSignals C1;
		
	//float s_temp[15] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
	//float a_temp[15] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	//int dest_temp = 10;
	//C1.setSignal(dest_temp, s[50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50], a[14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]);
	
	while(true) {
		while(C1.update_flag == true) {
			int m = 0;
		
			for ( auto i = C1.ctc_spd.begin(); i != C1.ctc_spd.end(); ++i) {
				*i = blocks[m].block_speed;
				m++;
			}
		
			int n = 0;
		
			for ( auto i = C1.ctc_auth.begin(); i != C1.ctc_auth.end(); ++i) {
				*i = blocks[n].block_authority;
				n++;
			}
			
			C1.update_flag = false;
			
			for (int i = 1; i <= block1.block_count; i++)  {
				blocks[i].setCircuit();
				blocks[i].setSpdAuth(C1.dest_block);
			}
		}
	}
	
	
	
	
	
	return 0;
}

