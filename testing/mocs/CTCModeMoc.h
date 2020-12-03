#ifndef CTCMODEMOC_H
#define CTCMODEMOC_H

#include <vector>
#include <iostream>
#include <string>

class CTCModeMoc
{
    private:
        bool mode;
    public:
        CTCModeMoc();
        void setMode(bool);
        bool getMode();
};

#endif // CTCMODE_H
