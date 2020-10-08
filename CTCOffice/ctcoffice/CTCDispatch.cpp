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
    float blockLength = 50;
    float trackLength = 10 * blockLength;
    for(int i = 0; i < 10; i++){
        authority.push_back(0);
    }

    if(getTimeStart() >= getTimeArrival()){
        return;
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
        qDebug() << "Incorrect Station Destination";
        return;
    }

    // TEST DEBUG FOR AUTHORITY
    for(int j = 0; j < 10; j++){
        qDebug() << "Authority at Block" << j << "- " << QString::number(authority.at(j)) << "km";
    }
}

void CTCDispatch::setSpeed(std::string station, float timeStart, float timeArrival)
{
    float duration = timeArrival - timeStart;
    float blockLength = 50;
    float trackLength = 10 * blockLength;
    float avgspeed = trackLength/duration;

    if(duration <= 0){
        qDebug() << "Invalid time frame: please try again.";
        return;
    }

    qDebug() << "Final Start Time: " << QString::number(timeArrival);
    qDebug() << "Final Arrival Time: " << QString::number(timeStart);
    qDebug() << "Duration of Trip: " << QString::number(duration);
    qDebug() << "Block Length: " << QString::number(blockLength);
    qDebug() << "Track Length: " << QString::number(trackLength);
    qDebug() << "Average Speed: " << QString::number(avgspeed);

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
        qDebug() << "Incorrect Station Destination";
    }

    // TEST DEBUG FOR SPEED
    for(int j = 0; j < 10; j++){
        qDebug() << "Suggested Speed at Block" << j << "- " << QString::number(speed.at(j)) << "km/hr";
    }
}

void CTCDispatch::setLine(std::string l){
    line = l;
    qDebug() << "Set Line to: " << QString::fromStdString(line);
}

std::string CTCDispatch::getline(){
    return line;
}

void CTCDispatch::setDestinationType(std::string dt){
    std::string temp = dt.substr(0,1);

    if(temp == "S"){
        setStation(dt);
    }
    if(temp == "B"){
        setBlock(dt);
    }

    destinationType = dt;
}

std::string CTCDispatch::getDestinationType(){
    return destinationType;
}

void CTCDispatch::setBlock(std::string blk){
    endblock = blk;
    qDebug() << "Set Block Destination to: " << QString::fromStdString(endblock);
}

std::string CTCDispatch::getBlock(){
    return endblock;
}

void CTCDispatch::setStation(std::string state){
    station = state;
    qDebug() << "Set Station Destination to: " << QString::fromStdString(station);
}

std::string CTCDispatch::getStation(){
    return station;
}

void CTCDispatch::setTimeStart(std::string st){
    qDebug() << "Set Start Time to: " << QString::fromStdString(st);

    float hours;
    float minutes;
    std::string shours;
    std::string sminutes;

    shours = st.substr(0,2);
    sminutes = st.substr(3,4);

    std::stringstream temp1(shours);
    std::stringstream temp2(sminutes);

    temp1 >> hours;
    temp2 >> minutes;

    float time = hours + (minutes/60);
    //qDebug() << "Start Time Math: " << QString::number(time);

    timeStart = time;
}

float CTCDispatch::getTimeStart(){
    return timeStart;
}

void CTCDispatch::setTimeArrival(std::string at){
    qDebug() << "Set Arrival Time to: " << QString::fromStdString(at);

    float hours;
    float minutes;
    std::string shours;
    std::string sminutes;

    shours = at.substr(0,2);
    sminutes = at.substr(3,4);

    std::stringstream temp1(shours);
    std::stringstream temp2(sminutes);

    temp1 >> hours;
    temp2 >> minutes;

    float time = hours + (minutes/60);
    //qDebug() << "Arrival Time Math: " << QString::number(time);

    timeArrival = time;
}

float CTCDispatch::getTimeArrival(){
    return timeArrival;
}

void CTCDispatch::dispatch(){

    setAuthority(station);
    setSpeed(station, timeStart, timeArrival);
    sendTrackController();
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

