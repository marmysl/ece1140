#include <iostream>
#include "CTCSignals.h"


void CTCSignals::setFlag(bool flag) {
	update_flag = flag;
}
void CTCSignals::setSignal(int b, float s[15], float a[15]) {
	dest_block = b;
	
	int len = *(&s + 1) - s;
	
	for(int i = 0; i < len; i++) {
		ctc_spd.push_back(s[i]);
		ctc_auth.push_back(a[i]);
	}
	setFlag(1);
}

