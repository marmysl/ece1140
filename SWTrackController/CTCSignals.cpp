#include <iostream>
#include "CTCSignals.h"
#include <vector>

bool CTCSignals::checkValidWayside(int id) {

    for (int i = 1; i < 24; i++) {
        if (i == id) {
            return true;
        }
    }

    return false;
}

bool CTCSignals::checkValidLine(std::string &line) {

    if (line == "Green Line") {
        return true;
    }
    else if (line == "Red Line") {
        return true;
    }
    else if (line == "Blue Line") {
        return true;
    }
    else {
        return false;
    }

}

CTCSignals::~CTCSignals() {
    delete [] blockptr;
    blockptr = NULL;
}

void CTCSignals::setUpArray(int block_count) {

    size = block_count;
    blockptr = new BlockInfoCTC[size];

    setUpExits();
}

void CTCSignals::setUpExits() {

    switch_id.push_back(std::make_pair(1, 5));

    switch_id.push_back(std::make_pair(2, 63));
    switch_id.push_back(std::make_pair(4, 77));
    switch_id.push_back(std::make_pair(5, 85));
    switch_id.push_back(std::make_pair(8, 28));
    switch_id.push_back(std::make_pair(10, 13));
    switch_id.push_back(std::make_pair(12, 57));

    switch_id.push_back(std::make_pair(14, 16));
    switch_id.push_back(std::make_pair(15, 9));
    switch_id.push_back(std::make_pair(17, 27));
    switch_id.push_back(std::make_pair(18, 33));
    switch_id.push_back(std::make_pair(19, 38));
    switch_id.push_back(std::make_pair(20, 44));
    switch_id.push_back(std::make_pair(22, 52));

    div_exit.push_back(std::make_pair(11, 5));

    div_exit.push_back(std::make_pair(0, 63));
    div_exit.push_back(std::make_pair(101, 77));
    div_exit.push_back(std::make_pair(100, 85));
    div_exit.push_back(std::make_pair(150, 28));
    div_exit.push_back(std::make_pair(1, 13));
    div_exit.push_back(std::make_pair(0, 57));

    div_exit.push_back(std::make_pair(15, 16));
    div_exit.push_back(std::make_pair(0, 9));
    div_exit.push_back(std::make_pair(76, 27));
    div_exit.push_back(std::make_pair(72, 33));
    div_exit.push_back(std::make_pair(71, 38));
    div_exit.push_back(std::make_pair(67, 44));
    div_exit.push_back(std::make_pair(66, 52));

    div_exit.push_back(std::make_pair(6, 5));

    div_exit.push_back(std::make_pair(64, 63));
    div_exit.push_back(std::make_pair(78, 77));
    div_exit.push_back(std::make_pair(86, 85));
    div_exit.push_back(std::make_pair(29, 28));
    div_exit.push_back(std::make_pair(14, 13));
    div_exit.push_back(std::make_pair(58, 57));

    div_exit.push_back(std::make_pair(1, 16));
    div_exit.push_back(std::make_pair(10, 9));
    div_exit.push_back(std::make_pair(28, 27));
    div_exit.push_back(std::make_pair(34, 33));
    div_exit.push_back(std::make_pair(39, 38));
    div_exit.push_back(std::make_pair(45, 44));
    div_exit.push_back(std::make_pair(53, 52));
}

int CTCSignals::getWaysideID(int block_id) {

    int temp_wayside_id = -1;
    for (int n = 0; n < size; n++) {
        if ( blockptr[n].block_id == block_id) {
            temp_wayside_id = blockptr[n].wayside_id;
        }
    }
    return temp_wayside_id;
}



void CTCSignals::setSpeed(float speed) {

    for (int i = 0; i < size; i++) {
        sug_speed_ctc.push_back(std::make_pair(i+1, speed));
   }

}

void CTCSignals::setAuthority(std::string &l, std::vector< std::pair<int, int> > auth) {

    while (checkValidLine(l)) {
        if(l == "Blue Line") {
            auto i = auth.begin();
            sug_auth_ctc_b.push_back(*i);
        }
        else {
            for (auto i= auth.begin(); i < auth.end(); i++) {
                if (l == "Green Line") {
                    sug_auth_ctc_g.push_back(*i);
                }
                else {
                    sug_auth_ctc_r.push_back(*i);
                }
            }
        }
    }
}

void CTCSignals::setExitBlocks(std::vector< std::pair<int, TrackModel::SwitchState> > states) {

    int temp_blockid;

    for (auto i = states.begin(); i < states.end(); i++){
        temp_blockid = i -> first;
        if ((i -> second) == TrackModel::SwitchState::SW_DIVERGING) {
            for (int m = 0; m < 23; m++) {
                if (temp_blockid == (div_exit[m].second)) {
                    exit_id.push_back( std::make_pair(switch_id[m].first, div_exit[m].first));
                }
            }
        }
        else {
            for (int m = 0; m < 23; m++) {
                if (temp_blockid == (str_exit[m].second)) {
                    exit_id.push_back( std::make_pair(switch_id[m].first, str_exit[m].first));
                }
            }
        }

    }
}

int CTCSignals::getWaysideExit(int w) {

    int temp = -1;
    for (auto i = exit_id.begin(); i < exit_id.end(); i++) {
        if ( w == (i -> first)) {
            temp = (i -> second);
        }
    }


    return temp;
}

float CTCSignals::getWaysideSpeed(int w) {
    float temp = -1;
    for (auto i = sug_speed_ctc.begin(); i < sug_speed_ctc.end(); i++) {
        if ( w == (i -> first)) {
            temp = (i -> second);
        }
    }

    return temp;
}

std::vector<std::pair<int,int> > CTCSignals::getWaysideAuth(int w, std::vector<int> a) {
    std::vector<std::pair<int,int> > temp;
    int blk_id;
    if (w == 1) {
        for (auto i = sug_auth_ctc_b.begin(); i < sug_auth_ctc_b.end(); i++) {
            temp.push_back(*i);
        }
    }
    else if (w < 14) {
        for (auto i = sug_auth_ctc_g.begin(); i < sug_auth_ctc_g.end(); i++) {
            for (auto m = a.begin(); m < a.end(); m++) {
                blk_id = *m;
                if ((i -> first) == blk_id) {
                    temp.push_back(*i);
                }
            }
        }
    }
    else {
        for (auto i = sug_auth_ctc_r.begin(); i < sug_auth_ctc_r.end(); i++) {
            for (auto m = a.begin(); m < a.end(); m++) {
                blk_id = *m;
                if ((i -> first) == blk_id) {
                    temp.push_back(*i);
                }
            }
        }
    }

    return temp;
}
