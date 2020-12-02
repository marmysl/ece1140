#ifndef TRACKLOGIC_H
#define TRACKLOGIC_H

#include <vector>

class TrackLogic
{
public:
    bool sug_speed;
    int sug_auth;
    std::vector<int> block_auth_commanded;
    bool route;
    int switch_head;
    int switch_tail_1;
    int switch_tail_2;
    int switch_state;
    std::vector<bool> block_occupancies;

    TrackLogic();


    void sendSuggested(float, int);
    bool checkRoute(bool);
    bool checkSpeed(int, bool);
    void setSwitch(int, int, int, bool);

};

#endif // TRACKLOGIC_H
