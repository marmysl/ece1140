#include "CTCDispatch.h"
#include <QDebug>
#include <string>
#include <sstream>
#include <QTextStream>
#include <QApplication>

//useful cout replacement command while using QT Creator Application Output
//qDebug() << QString::fromStdString(station);
//qDebug() << QString::number(hours);

void CTCDispatch::setAuthority(std::string station)
{
    qDebug() << QString::fromStdString(station);
    float blocklen = 50;
    if(station == "Station B"){
        for(int i = 9; i > -1; i--){
            if(i == 9){
                authority[i] = blocklen;
            }
            else{
                authority[i] = authority[i+1] + blocklen;
            }
        }
    }
    else if(station == "Station C"){
        for(int i = 9; i > -1; i--){
            if(i == 9){
                authority[i] = blocklen;
            }
            else{
                authority[i] = authority[i+1] + blocklen;
            }
        }
    }
    else{
        //std::cout << "Incorrect Station Destination" << endl;
        qDebug() << "Incorrect Station Destination";
    }

    // TEST DEBUG FOR AUTHORITY
    for(int j = 0; j < 10; j++){
        qDebug() << QString::number(authority[j]) << ", ";
    }
}

void CTCDispatch::setSpeed(std::string station, float timeStart, float timeArrival)
{
    float duration = timeArrival - timeStart;
    float blocklen = 50;
    float tracklength = 10 * blocklen;
    float avgspeed = tracklength/duration;

    qDebug() << "Start: " << QString::number(timeArrival);
    qDebug() << "Arrival: " << QString::number(timeStart);
    qDebug() << "Duration: " << QString::number(duration);
    qDebug() << "Blocklen: " << QString::number(blocklen);
    qDebug() << "Tracklength: " << QString::number(tracklength);
    qDebug() << "Avgspeed: " << QString::number(avgspeed);

    if(station == "Station B"){
        for(int i = 0; i < 10; i++){
            if(i < 3){
                speed[i] = (1.666666 * avgspeed);
            }
            else if(i >= 3 && i < 6){
                speed[i] = avgspeed;
            }
            else{
                speed[i] = ((-avgspeed*i) + (10*avgspeed))/4;
            }
        }
    }
    else if(station == "Station C"){
        for(int i = 0; i < 10; i++){
            if(i < 3){
                speed[i] = (1.666666 * avgspeed);
            }
            else if(i >= 3 && i < 6){
                speed[i] = avgspeed;
            }
            else{
                speed[i] = ((-avgspeed*(i+1)) + (10*avgspeed))/4;
            }
        }
    }
    else{
        //std::cout << "Incorrect Station Destination" << endl;
        qDebug() << "Incorrect Station Destination";
    }

    // TEST DEBUG FOR SPEED
    for(int j = 0; j < 10; j++){
        qDebug() << QString::number(speed[j]) << ", ";
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
    sig.setSignal(destblock, authority, speed);
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

