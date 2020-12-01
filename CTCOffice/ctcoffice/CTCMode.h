#ifndef CTCMODE_H
#define CTCMODE_H

#include <vector>
#include <iostream>
#include <string>

class CTCMode
{
    private:
    public:
        bool mode;
        CTCMode();
        void setMode(bool);
        bool getMode();
        void automaticDispatch();
        void manualDispatch();
        void sm(bool);

        CTCMode* m;

        int time;
};

#endif // CTCMODE_H
