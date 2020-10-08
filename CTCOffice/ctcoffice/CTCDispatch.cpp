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

void CTCDispatch::setAuthority(std::string station, int blocknum)
{
    float blockLength = 50;
    float trackLength;

    if(getTimeStart() >= getTimeArrival()){
        return;
    }


    if(station == "Station B" && blocknum == -1){
        int m = 0;
        trackLength = 10 * blockLength;

        for(int i = 0; i < 10; i++){
            authority.push_back(0);
        }
        for(auto i = authority.begin(); i != authority.end(); i++){
            if(m == 0){
                *i = trackLength;
            }
            else{
                *i = authority.at(m-1) - blockLength;
            }
            m++;
        }
        // TEST DEBUG FOR AUTHORITY
        for(int j = 0; j < 10; j++){
            qDebug() << "Authority at Block" << j << "- " << QString::number(authority.at(j)) << "km";
        }
    }
    else if(station == "Station C" && blocknum == -1){
        int n = 0;
        trackLength = 10 * blockLength;

        for(int i = 0; i < 10; i++){
            authority.push_back(0);
        }
        for(auto i = authority.begin(); i != authority.end(); i++){
            if(n == 0){
                *i = trackLength;
            }
            else{
                *i = authority.at(n-1) - blockLength;
            }
            n++;
        }
        // TEST DEBUG FOR AUTHORITY
        for(int j = 0; j < 10; j++){
            qDebug() << "Authority at Block" << j << "- " << QString::number(authority.at(j)) << "km";
        }
    }
    else if(blocknum != -1 && station == "-1"){
        int o = 0;
        trackLength = blocknum * blockLength;

        for(int i = 0; i < blocknum; i++){
            authority.push_back(0);
        }
        for(auto i = authority.begin(); i != authority.end(); i++){
            if(o == 0){
                *i = trackLength;
            }
            else{
                *i = authority.at(o-1) - blockLength;
            }
            o++;
        }
        // TEST DEBUG FOR AUTHORITY
        for(int j = 0; j < blocknum; j++){
            qDebug() << "Authority at Block" << j << "- " << QString::number(authority.at(j)) << "km";
        }
    }
    else{
        qDebug() << "Incorrect Station Destination";
        return;
    }
}

void CTCDispatch::setSpeed(std::string station, int blocknum, float timeStart, float timeArrival)
{
    float duration = timeArrival - timeStart;
    float blockLength = 50;
    float trackLength;
    float avgspeed;

    if(duration <= 0){
        qDebug() << "Invalid time frame: please try again.";
        return;
    }

    qDebug() << "Final Start Time: " << QString::number(timeArrival);
    qDebug() << "Final Arrival Time: " << QString::number(timeStart);
    qDebug() << "Duration of Trip: " << QString::number(duration);
    qDebug() << "Block Length: " << QString::number(blockLength);

    int m = 0;

    if(station == "Station B" && blocknum == -1){
        trackLength = 10 * blockLength;
        avgspeed = trackLength/duration;

        qDebug() << "Track Length: " << QString::number(trackLength);
        qDebug() << "Average Speed: " << QString::number(avgspeed);

        for(int i = 0; i < 10; i++){
            speed.push_back(0);
        }
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
        // TEST DEBUG FOR SPEED
        for(int j = 0; j < 10; j++){
            qDebug() << "Suggested Speed at Block" << j << "- " << QString::number(speed.at(j)) << "km/hr";
        }
    }
    else if(station == "Station C" && blocknum == -1){
        trackLength = 10 * blockLength;
        avgspeed = trackLength/duration;

        qDebug() << "Track Length: " << QString::number(trackLength);
        qDebug() << "Average Speed: " << QString::number(avgspeed);

        for(int i = 0; i < 10; i++){
            speed.push_back(0);
        }
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
        // TEST DEBUG FOR SPEED
        for(int j = 0; j < 10; j++){
            qDebug() << "Suggested Speed at Block" << j << "- " << QString::number(speed.at(j)) << "km/hr";
        }
    }
    else if(blocknum != -1 && station == "-1"){
        trackLength = blocknum * blockLength;
        avgspeed = trackLength/duration;

        qDebug() << "Track Length: " << QString::number(trackLength);
        qDebug() << "Average Speed: " << QString::number(avgspeed);

        for(int i = 0; i < blocknum; i++){
            speed.push_back(0);
        }
        for(auto i = speed.begin(); i != speed.end(); i++){
            *i = avgspeed;
        }
        // TEST DEBUG FOR SPEED
        for(int j = 0; j < blocknum; j++){
            qDebug() << "Suggested Speed at Block" << j << "- " << QString::number(speed.at(j)) << "km/hr";
        }
    }
    else{
        qDebug() << "Incorrect Station Destination";
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
        setBlock("-1");
    }
    if(temp == "B"){
        setBlock(dt);
        setStation("-1");
    }

    destinationType = dt;
}

std::string CTCDispatch::getDestinationType(){
    return destinationType;
}

void CTCDispatch::setBlock(std::string blk){
    if(blk != "-1"){
        std::string temp;
        int tblock;
        temp = blk.substr(5,6);

        std::stringstream temp1(temp);
        temp1 >> tblock;

        qDebug() << "Set Block Destination to: " << QString::number(tblock);
        if(tblock > 10){
            endblock = tblock - 5;
        }else{
            endblock = tblock;
        }
    }
    else{
        endblock = -1;
    }
}

int CTCDispatch::getBlock(){
    return endblock;
}

void CTCDispatch::setStation(std::string state){
    station = state;
    if(station != "-1"){
        qDebug() << "Set Station Destination to: " << QString::fromStdString(station);
    }
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

void CTCDispatch::dispatch(CTCSignals(&c)){
    setAuthority(station, endblock);
    setSpeed(station, endblock, timeStart, timeArrival);
    sendTrackController(c);
}

void CTCDispatch::sendTrackController(CTCSignals(&sig)){
    int destblock;
    if(station == "Station B"){
        destblock = 10;
    }else{
        destblock = 15;
    }
    sig.setSignal(destblock, speed, authority);
}

