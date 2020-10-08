#include "BlockCntrl.cpp"
#include "CTCSignals.h"


int main() {
	
	BlockContainer B_Container;
	
		
	using namespace std;
	for (int i = 0; i < 15; i++) {
		B_Container.addBlockObj(i);
	}
	
	
	for (int i = 0; i < 15; i++ )
		B_Container.blocks[i].getResult();
		
	
	
	CTCSignals C1;

		
    std::vector<float> s_temp {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
    std::vector<float> a_temp {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int dest_temp = 10;
    C1.setSignal(dest_temp, s_temp, a_temp);
	
	while(true) {
		
		while(C1.update_flag == true) {
			int m = 0;
		
			//for ( auto i = blocks.begin(); i != blocks.end(); ++i) {
				//i -> setSpdAuth(m+1, C1.ctc_spd.at(m), C1.ctc_auth.at(m));
				//i -> setCircuit();
				m++;
			//}
	
			C1.update_flag = false;
			
		}
		
		//for (auto i = blocks.begin(); i != blocks.end(); ++i) {
			//i -> setOcc();
		//}
	
	}

	return 0;
}

