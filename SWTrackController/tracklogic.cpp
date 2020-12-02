#include "tracklogic.h"

TrackLogic::TrackLogic()
{
    sug_speed = 0;
    sug_auth = 0;
    current_block_occ = 0;
    next_block_occ = 0;;
    route = 0;;
    switch_head = -1;
    switch_tail_1 = -1;
    switch_tail_2 = -1;
    switch_state = -1;
}

TrackLogic::TrackLogic(int switch_blocks[], int cross_b) {

    switch_head = switch_blocks[0];
    switch_tail_1 = switch_blocks[1];
    switch_tail_2 = switch_blocks[2];
    switch_state = 0;

    crossing_block = cross_b;
}


bool TrackLogic::checkRoute(bool temp_route) {
    if (switch_head == -1) {
        if (temp_route == 0) {
            route = 0;
            return true;
        }
        else { //temp_route == 1
            route = 0;
            return false;
        }
    }
    else {
        if (temp_route == 0) {
            if (switch_state == 0) {
                route = 0;
                return true;
            }
            else { //switch_state == 1
                route = 0;
                return false;
            }
        }
        else { //temp_route == 1
            if (switch_state == 0) {
                route = 1;
                return false;
            }
            else { //switch_state == 1
                route = 1;
                return true;
            }
        }
    }
}

bool TrackLogic::checkSpeed(bool speed, bool nocc) {
    bool safespeed = false;
    if (nocc == 1) {
        if (speed == 0) {
            safespeed = true;
        }
        else {
            safespeed = false;
        }
    }
    else {
        if (speed == 1) {
            safespeed = true;
        }
        else {
            safespeed = false;
        }
    }

    return safespeed;
}

bool TrackLogic::checkAuth(bool auth, bool nocc) {
    bool safeauthority = false;
    if (nocc == 1) {
        if (auth == 0) {
            safeauthority = true;
        }
        else {
            safeauthority = false;
        }
    }
    else {
        if (auth == 1) {
            safeauthority = true;
        }
        else {
            safeauthority = false;
        }
    }
    return safeauthority;
}

bool TrackLogic::setSwitch(bool new_pos) {
//setSwitchState( std::string route, int switchBlockId, SwitchState newDirection );
    if (new_pos == switch_state) {
        return false; //already set
    }
    else {
        return true; //changed in class, must be changed on track
    }
}

bool TrackLogic::activateCrossing(bool cross_block_occ) {
    if (crossing_block != -1) {
        if (cross_block_occ == true) {
            return true; //crossing should be active
        }
        else { // cross_block_occ == false
            return false; //crossing should not be active
        }
    }
    else { //crossing_block = -1 -> no crossing in wayside region
        return false; //crossing does not exist, should not be active
    }
}
