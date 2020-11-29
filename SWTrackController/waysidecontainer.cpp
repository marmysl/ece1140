#include "waysidecontainer.h"



WaysideContainer::WaysideContainer(int count)
{
    wayside_count = count;
    if (wayside_count == 1) {
        std::string line = "Blue Line";

        std::vector<char> s;
        s.push_back('A');
        s.push_back('B');
        s.push_back('C');

        std::vector<int> b;
        for (int i = 0; i <= 15; i++) {
            b.push_back(i);
        }

        int sw[4] = {5, 6, 11, 0};
        int fin[2] = {10, 15};
        addTrackObj(1, line, s, b, sw, 0, fin);
    }

    else if (wayside_count == 12) {
        std::string line = "Green Line";
    //wayside #1
        std::vector<char> s1;
        s1.push_back('J');
        s1.push_back('K');

        std::vector<int> b1;
        for (int i = 60; i <= 63; i++) {
            b1.push_back(i);
        }
        b1.push_back(0);
        b1.push_back(64);
        b1.push_back(65);

    //wayside #2
        std::vector<char> s2;
        s2.push_back('K');
        s2.push_back('L');

        std::vector<int> b2;
        for (int i = 65; i <= 74; i++) {
            b2.push_back(i);
        }
   //wayside #3
        std::vector<char> s3;
        s3.push_back('L');
        s3.push_back('M');
        s3.push_back('N');

        std::vector<int> b3;
        for (int i = 74; i <= 80; i++) {
            b3.push_back(i);
        }

        b3.push_back(101);
        b3.push_back(102);
   //wayside #4
            std::vector<char> s4;
            s4.push_back('N');
            s4.push_back('O');
            s4.push_back('Q');
            s4.push_back('R');

            std::vector<int> b4;
            for (int i = 80; i <= 88; i++) {
                b4.push_back(i);
            }
            for (int i = 98; i <= 101; i++) {
                b4.push_back(i);
            }
  //wayside #5
            std::vector<char> s5;
            s5.push_back('O');
            s5.push_back('P');
            s5.push_back('Q');

            std::vector<int> b5;
            for (int i = 88; i <= 98; i++) {
                b5.push_back(i);
            }
  //wayside #6
            std::vector<char> s6;
            s6.push_back('V');
            s6.push_back('W');

            std::vector<int> b6;
            for (int i = 120; i <= 140; i++) {
                b6.push_back(i);
            }
  //wayside #7
            std::vector<char> s7;
            s7.push_back('F');
            s7.push_back('G');
            s7.push_back('W');
            s7.push_back('X');
            s7.push_back('Y');
            s7.push_back('Z');

            std::vector<int> b7;
            for (int i = 140; i <= 151; i++) {
                b7.push_back(i);
            }
            for (int i = 27; i <= 32; i++) {
                b7.push_back(i);
            }
  //wayside #8
            std::vector<char> s8;
            s8.push_back('D');
            s8.push_back('E');
            s8.push_back('F');

            std::vector<int> b8;
            for (int i = 16; i <= 27; i++) {
                b8.push_back(i);
            }
  //wayside #9
            std::vector<char> s9;
            s9.push_back('A');
            s9.push_back('B');
            s9.push_back('C');
            s9.push_back('D');

            std::vector<int> b9;
            for (int i = 1; i <= 16; i++) {
                b9.push_back(i);
            }
  //wayside #10
            std::vector<char> s10;
            s10.push_back('G');
            s10.push_back('H');
            s10.push_back('I');

            std::vector<int> b10;
            for (int i = 32; i <= 52; i++) {
                b10.push_back(i);
            }
  //wayside #11
            std::vector<char> s11;
            s11.push_back('I');
            s11.push_back('J');

            std::vector<int> b11;
            for (int i = 52; i <= 60; i++) {
                b11.push_back(i);
            }
  //wayside 12
            std::vector<char> s13;
            s13.push_back('S');
            s13.push_back('T');
            s13.push_back('U');
            s13.push_back('V');

            std::vector<int> b13;
            for (int i = 102; i <= 120; i++) {
                b13.push_back(i);
            }

            int sw1[4] = {63, 64, 0, 0};
            int sw2[4] = {77, 78, 101, 0};
            int sw3[4] = {85, 86, 100, 0};
            int sw4[4] = {28, 29, 150, 0};
            int sw5[4] = {13, 14, 1, 0};
            int sw6[4] = {57, 58, 0, 0};
            int swX[4] = {-1,-1,-1,-1};

            int fin1[2] = {65, 0};
            int fin2[2] = {74, -1};
            int fin3[2] = {80,102};
            int fin4[2] = {88, 101};
            int fin5[2] = {98, -1};
            int fin6[2] = {140, -1};
            int fin7[2] = {32, 150};
            int fin8[2] = {27, -1};
            int fin9[2] = {16, -1};
            int fin10[2] = {52, -1};
            int fin11[2] = {60, 0};
            int fin12[2] = {120, -1};

    addTrackObj(1, line, s1, b1, sw1, 0, fin1);
    addTrackObj(2, line, s2, b2, swX, 0, fin2);
    addTrackObj(3, line, s3, b3, sw2, 0, fin3);
    addTrackObj(4, line, s4, b4, sw3, 0, fin4);
    addTrackObj(5, line, s5, b5, swX, 0, fin5);
    addTrackObj(6, line, s6, b6, swX, 0, fin6);
    addTrackObj(7, line, s7, b7, sw4, 0, fin7);
    addTrackObj(8, line, s8, b8, swX, 19, fin8);
    addTrackObj(9, line, s9, b9, sw5, 0, fin9);
    addTrackObj(10, line, s10, b10, swX, 0, fin10);
    addTrackObj(11, line, s11, b11, sw6, 0, fin11);
    addTrackObj(12, line, s13, b13, swX, 0, fin12);

    }

    else if (wayside_count == 10) {
        std::string line = "Red Line";

        //wayside #1
        std::vector<char> b1;
        b1.push_back('A');
        b1.push_back('F');
        b1.push_back('E');

        std::vector<int> s1;
        for (int i = 0; i <= 3; i++) {
            s1.push_back(i);
        }
        for (int i = 13; i <= 18; i++) {
            s1.push_back(i);
        }

        //wayside #2
        std::vector<char> b2;
        b2.push_back('B');
        b2.push_back('C');
        b2.push_back('D');
        b2.push_back('E');

        std::vector<int> s2;
        for (int i = 3; i <= 13; i++) {
            s2.push_back(i);
        }

        //wayside #3
        std::vector<char> b3;
        b3.push_back('F');
        b3.push_back('G');

        std::vector<int> s3;
        for (int i = 18; i <= 32; i++) {
            s3.push_back(i);
        }

        //wayside #4
        std::vector<char> b4;
        b4.push_back('G');
        b4.push_back('H');
        b4.push_back('T');
        b4.push_back('S');

        std::vector<int> s4;
        for (int i = 23; i <= 30; i++) {
            s4.push_back(i);
        }
        for (int i = 74; i <= 76; i++) {
            s4.push_back(i);
        }

        //wayside #5
        std::vector<char> b5;
        b5.push_back('S');
        b5.push_back('R');
        b5.push_back('H');

        std::vector<int> s5;
        for (int i = 30; i <= 35; i++) {
            s5.push_back(i);
        }
        for (int i = 72; i <= 74; i++) {
            s5.push_back(i);
        }

        //wayside #6
        std::vector<char> b6;
        b6.push_back('H');
        b6.push_back('P');
        b6.push_back('Q');
        b6.push_back('R');

        std::vector<int> s6;
        for (int i = 35; i <= 40; i++) {
            s6.push_back(i);
        }
        for (int i = 69; i <= 72; i++) {
            s6.push_back(i);
        }

        //wayside #7
        std::vector<char> b7;
        b7.push_back('H');
        b7.push_back('P');
        b7.push_back('O');

        std::vector<int> s7;
        for (int i = 40; i <= 46; i++) {
            s7.push_back(i);
        }
        for (int i = 67; i <= 69; i++) {
            s7.push_back(i);
        }

        //wayside #8
        std::vector<char> b8;
        b8.push_back('I');
        b8.push_back('J');

        std::vector<int> s8;
        for (int i = 46; i <= 50; i++) {
            s8.push_back(i);
        }

        //wayside #9
        std::vector<char> b9;
        b9.push_back('J');
        b9.push_back('N');

        std::vector<int> s9;
        for (int i = 50; i <= 54; i++) {
            s9.push_back(i);
        }
        for (int i = 64; i <= 66; i++) {
            s9.push_back(i);
        }

        //wayside #10
        std::vector<char> b10;
        b10.push_back('J');
        b10.push_back('K');
        b10.push_back('L');
        b10.push_back('M');

        std::vector<int> s10;
        for (int i = 54; i <= 64; i++) {
            s10.push_back(i);
        }

        int sw1[4] = {16, 1, 15, 0};
        int sw2[4] = {9, 10, 0, 0};
        int sw3[4] = {27, 28, 76, 0};
        int sw4[4] = {33, 34, 72, 0};
        int sw5[4] = {38, 39, 71, 0};
        int sw6[4] = {44, 45, 67, 0};
        int sw7[4] = {52, 53, 66, 0};
        int swX[4] = {-1,-1,-1,-1};

        int fin1[2] = {3, 13};
        int fin2[2] = {10, 0};
        int fin3[2] = {20, -1};
        int fin4[2] = {30, 76};
        int fin5[2] = {30, 72};
        int fin6[2] = {40, 72};
        int fin7[2] = {40, 67};
        int fin8[2] = {50, -1};
        int fin9[2] = {54, 64};
        int fin10[2] = {64, -1};

        addTrackObj(1, line, b1, s1, sw1, 0, fin1);
        addTrackObj(2, line, b2, s2, sw2, 0, fin2);
        addTrackObj(3, line, b3, s3, swX, 0, fin3);
        addTrackObj(4, line, b4, s4, sw3, 0, fin4);
        addTrackObj(5, line, b5, s5, sw4, 0, fin5);
        addTrackObj(6, line, b6, s6, sw5, 0, fin6);
        addTrackObj(7, line, b7, s7, sw6, 0, fin7);
        addTrackObj(8, line, b8, s8, swX, 47, fin8);
        addTrackObj(9, line, b9, s9, sw7, 0, fin9);
        addTrackObj(10, line, b10, s10, swX, 0, fin10);

    }
}


void WaysideContainer::addTrackObj(int id, std::string &line, std::vector<char> &s, std::vector<int> &b, int sw[4], int cr, int f[2]) {

    TrackController t;
    t.setUpController(id, line, s, b, sw, cr, f);
    waysides.push_back(t);

    for(auto i = b.begin(); i != b.end(); i++){
        t.addBlockObj(*i);
    }

}


void WaysideContainer::addCTCObj(CTCSignals &ctc_track_controller) {
    wayside_signals = ctc_track_controller;

   if (wayside_count > 1) {
       for (auto i = waysides.begin(); i != waysides.end(); i++) {
           i -> setSignalsInstance(wayside_signals);
       }
   }
   else {
      auto i = waysides.begin();
      i -> setSignalsInstance(wayside_signals);
   }

}
