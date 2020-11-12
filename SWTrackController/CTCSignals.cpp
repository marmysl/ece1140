#include <iostream>
#include "CTCSignals.h"
#include <vector>


std::vector<bool> CTCSignals::calcRoute(std::string &l, std::vector<int>r) {

    std::vector<bool> temp;
    return temp;

}

int CTCSignals::setSignal(std::string &l, std::vector<bool> routes) {


        if (l == "Green Line") {
            int j = 0;
            for(auto i = routes.begin(); i != routes.end(); i++) {
                green_route[j] = *i;
                j++;
            }
        }
        else if (l == "Red Line") {
            int j = 0;
            for(auto i = routes.begin(); i != routes.end(); i++) {
                red_route[j] = *i;
                j++;
            }
        }
        else if (l == "Blue Line") {
            int j = 0;
            for(auto i = routes.begin(); i != routes.end(); i++) {
                blue_route[j] = *i;
                j++;
            }
        }
        else {
            return -1;
        }

        return 0;
}

std::vector<float> CTCSignals::getSpeed(int w_id, std::string &line) {
    std::vector<float> temp_speed;

    if (line == "Green Line") {
        if (w_id == 1) {
            for (auto i = gspeed1.begin(); i != gspeed1.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 2) {
            for (auto i = gspeed2.begin(); i != gspeed2.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 3) {
            for (auto i = gspeed3.begin(); i != gspeed3.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 4) {
            for (auto i = gspeed4.begin(); i != gspeed4.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 5) {
            for (auto i = gspeed5.begin(); i != gspeed5.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 6) {
            for (auto i = gspeed6.begin(); i != gspeed6.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 7) {
            for (auto i = gspeed7.begin(); i != gspeed7.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 8) {
            for (auto i = gspeed8.begin(); i != gspeed8.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 9) {
            for (auto i = gspeed9.begin(); i != gspeed9.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 10) {
            for (auto i = gspeed10.begin(); i != gspeed10.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 11) {
            for (auto i = gspeed11.begin(); i != gspeed11.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 12) {
            for (auto i = gspeed12.begin(); i != gspeed12.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else {
            temp_speed.push_back(-1);
        }
    }

    else if (line == "Red Line") {
        if (w_id == 1) {
            for (auto i = rspeed1.begin(); i != rspeed1.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 2) {
            for (auto i = rspeed2.begin(); i != rspeed2.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 3) {
            for (auto i = rspeed3.begin(); i != rspeed3.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 4) {
            for (auto i = rspeed4.begin(); i != rspeed4.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 5) {
            for (auto i = rspeed5.begin(); i != rspeed5.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 6) {
            for (auto i = rspeed6.begin(); i != rspeed6.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 7) {
            for (auto i = rspeed7.begin(); i != rspeed7.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 8) {
            for (auto i = rspeed8.begin(); i != rspeed8.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 9) {
            for (auto i = rspeed9.begin(); i != rspeed9.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else if (w_id == 10) {
            for (auto i = rspeed10.begin(); i != rspeed10.end(); i++) {
                temp_speed.push_back(*i);
            }
        }
        else {
            temp_speed.push_back(-1);
        }
    }

    else if (line  == "Blue Line") {
        for (auto i = bspeed1.begin(); i != bspeed1.end(); i++) {
            temp_speed.push_back(*i);
        }
    }

    else {
        temp_speed.push_back(-1);
    }

    return temp_speed;
}

std::vector<int> CTCSignals::getAuth(int w_id, std::string &line) {
    std::vector<int> temp_auth;

    if (line == "Green Line") {
        if (w_id == 1) {
            for (auto i = gauth1.begin(); i != gauth1.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 2) {
            for (auto i = gauth2.begin(); i != gauth2.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 3) {
            for (auto i = gauth3.begin(); i != gauth3.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 4) {
            for (auto i = gauth4.begin(); i != gauth4.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 5) {
            for (auto i = gauth5.begin(); i != gauth5.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 6) {
            for (auto i = gauth6.begin(); i != gauth6.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 7) {
            for (auto i = gauth7.begin(); i != gauth7.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 8) {
            for (auto i = gauth8.begin(); i != gauth8.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 9) {
            for (auto i = gauth9.begin(); i != gauth9.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 10) {
            for (auto i = gauth10.begin(); i != gauth10.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 11) {
            for (auto i = gauth11.begin(); i != gauth11.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 12) {
            for (auto i = gauth12.begin(); i != gauth12.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else {
            temp_auth.push_back(-1);
        }
    }

    else if (line == "Red Line") {
        if (w_id == 1) {
            for (auto i = rauth1.begin(); i != rauth1.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 2) {
            for (auto i = rauth2.begin(); i != rauth2.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 3) {
            for (auto i = rauth3.begin(); i != rauth3.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 4) {
            for (auto i = rauth4.begin(); i != rauth4.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 5) {
            for (auto i = rauth5.begin(); i != rauth5.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 6) {
            for (auto i = rauth6.begin(); i != rauth6.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 7) {
            for (auto i = rauth7.begin(); i != rauth7.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 8) {
            for (auto i = rauth8.begin(); i != rauth8.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 9) {
            for (auto i = rauth9.begin(); i != rauth9.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else if (w_id == 10) {
            for (auto i = rauth10.begin(); i != rauth10.end(); i++) {
                temp_auth.push_back(*i);
            }
        }
        else {
            temp_auth.push_back(-1);
        }
    }

    else if (line  == "Blue Line") {
        for (auto i = bauth1.begin(); i != bauth1.end(); i++) {
            temp_auth.push_back(*i);
        }
    }

    else {
        temp_auth.push_back(-1);
    }

    return temp_auth;
}

bool  CTCSignals::getRoute(int w_id, std::string &line) {
    bool temp_route;

    if (line == "Green Line") {
        int j = 1;
        for (auto i = green_route.begin(); i != green_route.end(); i++) {
            if (j == w_id) {
                bool m = bool(*i);
                temp_route = m;
            }
            j++;
        }
    }

    else if (line == "Red Line") {
        int j = 1;
        for (auto i = red_route.begin(); i != red_route.end(); i++) {
            if (j == w_id) {
                bool m = bool(*i);
                temp_route = m;
            }
            j++;
        }
    }

    else if (line  == "Blue Line") {
        auto i = blue_route.begin();
        bool m = bool(*i);
        temp_route = m;
    }

    else {
        return -1;
    }

    return temp_route;
}
