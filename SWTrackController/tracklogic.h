#ifndef TRACKLOGIC_H
#define TRACKLOGIC_H

#include <vector>

class TrackLogic
{
public:
    bool sug_speed;
    bool sug_auth;
    bool current_block_occ, next_block_occ;
    bool route;
    int switch_head;
    int switch_tail_1;
    int switch_tail_2;
    int switch_state;
    int crossing_block;

    TrackLogic();
    TrackLogic(int[], int);

    //void sendSuggested(float, int);
    bool checkRoute(bool); //bool - route to be set; returns bool for if switch must be changed
    bool checkSpeed(bool, bool); //bool - speed > 0, bool - next block occupancy; returns true if safe, false if not.
    bool checkAuth(bool, bool); //bool - authority > 0, bool - next block occupancy; returns true if safe, false if not.
    bool setSwitch(bool); //bool - switch state to be set; returns true for changed, false if already set;
    bool activateCrossing(bool); //bool - crossing block occupancy; returns true if crossing should be active, false if not or no crossing.


};

#endif // TRACKLOGIC_H
