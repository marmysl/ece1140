#include "CTCModeMoc.h"

CTCModeMoc::CTCModeMoc()
{
    mode = 0;
}

void CTCModeMoc::setMode(bool m){

    if(m == 0){
        mode = 0;
    }
    else{
        mode = 1;
    }
}

bool CTCModeMoc::getMode(){
    return mode;
}
