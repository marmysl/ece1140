//ADD GUARD
#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H


#include "../TrackModel/tracklayout.hpp"
#include "../TrackModel/trackmodel_controller.hpp"
#include "../TrackModel/trackmodel_main.hpp"
#include <iostream>
#include <vector>

struct BlockInfoCTC {

    int wayside_id;
    int section;
    int block_id;
    int failure_code;
    bool occupancy;

};

class CTCSignals {

private:

    //std::vector<int, std::vector<float>> sug_speed_ctc --
    // int -- wayside ID
    // std::vector<float> -- vector of suggested speed values set by CTC
    std::vector< std::pair<int, float> > sug_speed_ctc;

    //std::vector<int, std::vector<float>> sug_auth_ctc --
    // int -- wayside ID
    // std::vector<int> -- vector of suggested authority values set by CTC
    std::vector< std::pair<int, int> > sug_auth_ctc_g;
    std::vector< std::pair<int, int> > sug_auth_ctc_r;
    std::vector< std::pair<int, int> > sug_auth_ctc_b;

    //std::vector<int, int> exit id --
    //int -- wayside ID
    //int -- exit block ID
    std::vector< std::pair<int, int> > exit_id;

    //int -- wayside ID
    //int -- switch block ID
    std::vector< std::pair<int, int> > div_exit;
    std::vector< std::pair<int, int> > str_exit;
    std::vector< std::pair<int, int> > switch_id;
    int size;
    bool checkValidWayside(int);
    bool checkValidLine(std::string&);

public:

    struct BlockInfoCTC *blockptr = NULL;

    std::vector< std::pair<int, TrackModel::SwitchState> > switchstates; //<block_id, switch state>

    ~CTCSignals();
    void setUpArray(int);
    int getWaysideID(int);
    void setUpExits();

    //FOR CTC USE
    void setSpeed(float);

    void setAuthority(std::string &, std::vector< std::pair<int, int> >);
    //pair <block #, authority>

    void setExitBlocks(std::vector< std::pair<int, TrackModel::SwitchState> >);
    //returns exit blocks in a vector, call setLineExit with return vector as parameter

    //bool setLineExit(std::string &, std::vector<int>);


    //FOR WAYSIDE USE
    float getWaysideSpeed(int);
    std::vector<std::pair<int, int> > getWaysideAuth(int, std::vector<int>);
    int getWaysideExit(int);

};



//END GUARD
#endif
