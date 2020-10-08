#include "CTCDispatch.h"
#include <QDebug>
#include <string>
#include <sstream>
#include <QTextStream>
#include <QApplication>

//useful cout replacement command while using QT Creator Application Output
//qDebug() << QString::fromStdString(station);
//qDebug() << QString::number(hours);

//Get block 6
/*Route *rt;
rt = getRoute("Blue Line");
Block* blk6 = rt -> getBlock(6);

while(prevBlock != NULL)
Block* blk5 = blk6 -> prevBlock;*/

void CTCDispatch::setAuthority(std::string station)
{
    qDebug() << QString::fromStdString(station);
    float blockLength = 50;
    float trackLength = 10 * blockLength;
    for(int i = 0; i < 10; i++){
        authority.push_back(0);
    }

    if(station == "Station B"){
        int m = 0;

        for(auto i = authority.begin(); i != authority.end(); i++){
            if(m == 0){
                *i = trackLength;
            }
            else{
                *i = authority.at(m-1) - blockLength;
            }
            m++;
        }
    }
    else if(station == "Station C"){
        int n = 0;

        for(auto i = authority.begin(); i != authority.end(); i++){
            if(n == 0){
                *i = trackLength;
            }
            else{
                *i = authority.at(n-1) - blockLength;
            }
            n++;
        }
    }
    else{
        //std::cout << "Incorrect Station Destination" << endl;
        qDebug() << "Incorrect Station Destination";
    }

    // TEST DEBUG FOR AUTHORITY
    for(int j = 0; j < 10; j++){
        qDebug() << QString::number(authority.at(j)) << ", ";
    }
}

void CTCDispatch::setSpeed(std::string station, float timeStart, float timeArrival)
{
    float duration = timeArrival - timeStart;
    float blockLength = 50;
    float trackLength = 10 * blockLength;
    float avgspeed = trackLength/duration;

    qDebug() << "Start: " << QString::number(timeArrival);
    qDebug() << "Arrival: " << QString::number(timeStart);
    qDebug() << "Duration: " << QString::number(duration);
    qDebug() << "Blocklen: " << QString::number(blockLength);
    qDebug() << "Tracklength: " << QString::number(trackLength);
    qDebug() << "Avgspeed: " << QString::number(avgspeed);

    for(int i = 0; i < 10; i++){
        speed.push_back(0);
    }
    int m = 0;

    if(station == "Station B"){
        for(auto i = speed.begin(); i != speed.end(); i++){
            if(m < 3){
                *i = (1.666666 * avgspeed);
            }
            else if(m >= 3 && m < 6){
                *i = avgspeed;
            }
            else{
                *i = ((-avgspeed*(m+1)) + (10*avgspeed))/4;
            }
            m++;
        }
    }
    else if(station == "Station C"){
        for(auto i = speed.begin(); i != speed.end(); i++){
            if(m < 3){
                *i = (1.666666 * avgspeed);
            }
            else if(m >= 3 && m < 6){
                *i = avgspeed;
            }
            else{
                *i = ((-avgspeed*(m)) + (10*avgspeed))/4;
            }
            m++;
        }
    }
    else{
        //std::cout << "Incorrect Station Destination" << endl;
        qDebug() << "Incorrect Station Destination";
    }

    // TEST DEBUG FOR SPEED
    for(int j = 0; j < 10; j++){
        qDebug() << QString::number(speed.at(j)) << ", ";
    }
}

void CTCDispatch::sendTrackController(){
    CTCSignals sig;
    int destblock;
    if(station == "Station B"){
        destblock = 10;
    }else{
        destblock = 15;
    }
    sig.setSignal(destblock, speed, authority);
}


void CTCDispatch::setLine(std::string l){
    line = l;
    qDebug() << QString::fromStdString(line);
}

std::string CTCDispatch::getline(){
    return line;
}

void CTCDispatch::setStation(std::string state){
    station = state;
    qDebug() << QString::fromStdString(station);
}

std::string CTCDispatch::getStation(){
    return station;
}

void CTCDispatch::setTimeStart(std::string st){
    float hours;
    float minutes;
    std::string shours;
    std::string sminutes;

    shours = st.substr(0,2);
    sminutes = st.substr(3,4);
    //qDebug() << QString::fromStdString(st);
    //qDebug() << QString::fromStdString(shours);
    //qDebug() << QString::fromStdString(sminutes);

    std::stringstream temp1(shours);
    std::stringstream temp2(sminutes);

    temp1 >> hours;
    temp2 >> minutes;
    //qDebug() << QString::number(hours);
    //qDebug() << QString::number(minutes);

    float time = hours + (minutes/60);
    qDebug() << QString::number(time);

    timeStart = time;
}

float CTCDispatch::getTimeStart(){
    return timeStart;
}

void CTCDispatch::setTimeArrival(std::string at){
    float hours;
    float minutes;
    std::string shours;
    std::string sminutes;

    shours = at.substr(0,2);
    sminutes = at.substr(3,4);
    //qDebug() << QString::fromStdString(st);
    //qDebug() << QString::fromStdString(shours);
    //qDebug() << QString::fromStdString(sminutes);

    std::stringstream temp1(shours);
    std::stringstream temp2(sminutes);

    temp1 >> hours;
    temp2 >> minutes;
    //qDebug() << QString::number(hours);
    //qDebug() << QString::number(minutes);

    float time = hours + (minutes/60);
    qDebug() << QString::number(time);

    timeArrival = time;
}

float CTCDispatch::getTimeArrival(){
    return timeArrival;
}

void CTCDispatch::dispatch(){
    //qDebug() << QString::fromStdString(station) << Qt::endl;
    //qDebug() << QString::number(timeStart) << Qt::endl;
    //qDebug() << QString::number(timeArrival) << Qt::endl;

    setAuthority(station);
    setSpeed(station, timeStart, timeArrival);
    sendTrackController();
}

