#include "CTCMode.h"
#include <QDebug>
#include <string>
#include <sstream>
#include <QTextStream>
#include <QApplication>

#include "system_main.h"

// mode = 0 = Automatic
// mode = 1 = Manual
CTCMode::CTCMode()
{
    mode = 0;
}

void CTCMode::setMode(bool m){
    mode = m;

    if(m == 0){
        automaticDispatch();
        qDebug() << "Set Dispatch Mode to Automatic";
    }
    else if(m == 1){
        manualDispatch();
        qDebug() << "Set Dispatch Mode to Manual";
    }
    else{
        //throw error
    }
}

bool CTCMode::getMode(){
    return mode;
}

void CTCMode::automaticDispatch(){

}

void CTCMode::manualDispatch(){

}
