//This file contains a class declaration
#ifndef TrackController_h
#define TrackController_h
#include <vector>


//FlashLight class declaration
class TrackController
{

    public:
        int region;
        std::vector<char> cntrl_sections;
        std::vector<int> cntrl_blocks;
        std::vector<int> cntrl_switches;
        //int *cntrl_crossings;
        int block_count;
        int section_length;
        int section_count;
        TrackController(); //Constructor
        int getResult() const;
        //TrackController(region);
};

#endif /*TrackController_h*/
