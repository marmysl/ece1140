#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

#include <iostream>
#include <vector>


class CTCSignals
{
	public:
		bool update_flag = false;
		int dest_block;
		std::vector<float> ctc_spd;
		std::vector<float> ctc_auth;
		void setSignal(int b, std::vector<float> &s, std::vector<float> &a) {
			dest_block = b;
	
			for(int i = 0; i < s.size(); i++) {
				ctc_spd.push_back(s[i]);
				ctc_auth.push_back(a[i]);
			}
			update_flag = true;
		}
		
};


#endif
