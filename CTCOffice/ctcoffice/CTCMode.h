#ifndef CTCMODE_H
#define CTCMODE_H

#include <vector>
#include <iostream>
#include <string>

class CTCMode
{
    private:
        bool mode;
    public:
        CTCMode();
        void setMode(bool);
        bool getMode();
        void automaticDispatch();
        void manualDispatch();
};

#endif // CTCMODE_H
