//ADD GUARD
#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

#include <iostream>
#include <vector>


class CTCSignals {

public:

    std::vector<float> gspeed1, gspeed2, gspeed3, gspeed4, gspeed5, gspeed6, gspeed7, gspeed8, gspeed9, gspeed10, gspeed11, gspeed12;
    std::vector<int> gauth1, gauth2, gauth3, gauth4, gauth5, gauth6, gauth7, gauth8, gauth9, gauth10, gauth11, gauth12;
    std::vector<float> rspeed1, rspeed2, rspeed3, rspeed4, rspeed5, rspeed6, rspeed7, rspeed8, rspeed9, rspeed10;
    std::vector<int> rauth1, rauth2, rauth3, rauth4, rauth5, rauth6, rauth7, rauth8, rauth9, rauth10;
    std::vector<float> bspeed1;
    std::vector<int> bauth1;

    std::vector<bool> green_route, red_route, blue_route; //vector<bool> - route per wayside, 0 -> straight & 1 -> diverging

    std::vector<bool> calcRoute(std::string &, std::vector<int>); //string line - of which track line, vector<int> - route in order of ascending order

    int setSignal(std::string &, std::vector<bool>); //string line - of which track line, vector<int> exits - vector of routes
    std::vector<float> getSpeed(int, std::string &);
    std::vector<int> getAuth(int, std::string &);
    bool getRoute(int, std::string &); //int wayside_id - specify which route is requested, string line - of which track line


};

//END GUARD
#endif
