#ifndef CTCMODE_H
#define CTCMODE_H

#include <vector>
#include <iostream>
#include <string>
#include <QObject>
class CTCDispatch;

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

        int timerID;
        int time;
        std::string line;

        void test(CTCDispatch train);
};

#endif // CTCMODE_H
