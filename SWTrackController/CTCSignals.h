#include <iostream>
#include <vector>


class CTCSignals
{
	private:
		void setFlag(bool);
	public:
		bool update_flag = 0;
		int dest_block;
		void setSignal(int, float[], float[]);
		std::vector<float> ctc_spd;
		std::vector<float> ctc_auth;
};


