#ifndef TRACKCONTROLLER_H
#define TRACKCONTROLLER_H

#include <vector>

class TrackController
{
public:
    TrackController();
    int region;
    std::vector<char> cntrl_sections;
    std::vector<int> cntrl_blocks;
    std::vector<int> cntrl_switches;
    int block_count;
    int section_length;
    int section_count;
    int getResult();
};

#endif // TRACKCONTROLLER_H


