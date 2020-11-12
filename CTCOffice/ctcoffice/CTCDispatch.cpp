#include "CTCDispatch.h"
#include <QDebug>
#include <string>
#include <sstream>
#include <QTextStream>
#include <QApplication>
#include "../../TrackModel/tracklayout.hpp"
#include "system_main.h"
#include <cmath>


//useful cout replacement command while using QT Creator Application Output
//qDebug() << QString::fromStdString(station);
//qDebug() << QString::number(hours);

//Get block 6
/*Route *rt;
rt = getRoute("Blue Line");
Block* blk6 = rt -> getBlock(6);

while(prevBlock != NULL)
Block* blk5 = blk6 -> prevBlock;*/

void CTCDispatch::setAuthority()
{
        TrackModel::TrainPathInfo route;
        route = findRoute();

        int auth = route.blocks.size();
        for(auto val : route.blocks){
            authority.push_back(auth);
            auth--;
            qDebug() << "Set Authority at Block " << val->id << ": " << QString::number(auth);
        }
}

void CTCDispatch::setSpeed(float timeStart, float timeArrival)
{
    TrackModel::TrainPathInfo route;
    route = findRoute();
    float totalBlockLength = 0;

    for(auto val : route.blocks){
        totalBlockLength += val->length;
    }

    totalBlockLength = totalBlockLength/1000;
    speed = totalBlockLength/(timeArrival-timeStart);
    qDebug() << "Set Speed to: " << QString::number(speed);
}

void CTCDispatch::setLine(std::string l){
    line = l;
    qDebug() << "Set Line to: " << QString::fromStdString(line);
}

std::string CTCDispatch::getline(){
    return line;
}

void CTCDispatch::setDestination(QString dest, QString destType){
    if(destType == "Station"){
        setStation(dest.toStdString());
    }
    if(destType == "Block"){
        setBlock(dest.toInt());
    }
}

void CTCDispatch::setBlock(int blk){
    if(blk != -1){
        qDebug() << "Set Block Destination to: " << QString::number(blk);
        endblock = blk;
    }
    else{
        endblock = -1;
    }
}

int CTCDispatch::getBlock(){
    return endblock;
}

void CTCDispatch::setStation(std::string state){
    int startnum, endnum;
    std::string blknum;

    startnum = state.find('(');
    endnum = state.find(')');

    blknum = state.substr(startnum + 1, (endnum - startnum) -1);

    std::stringstream temp1(blknum);
    temp1 >> endblock;
    qDebug() << "Block: " << QString::number(endblock);
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
    qDebug() << "Start Time Math: " << QString::number(time);

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
    qDebug() << "Arrival Time Math: " << QString::number(time);

    timeArrival = time;
}

float CTCDispatch::getTimeArrival(){
    return timeArrival;
}

void CTCDispatch::setPassNum(){
    passNum = rand() % 220;
}

float CTCDispatch::getPassNum(){
    return passNum;
}

void CTCDispatch::dispatch(CTCSignals(&c)){
    setPassNum();
    carsNum = ceil(passNum/44); // ceil is taken out
    //qDebug() << "Number of Passengers on Train: " << QString::number(passNum);
    //qDebug() << "Number of Cars on Train: " << QString::number(carsNum);

    setAuthority();
    setSpeed(timeStart, timeArrival);

    sendTrackController(c);

    createNewTrain(m, carsNum, line);
}

void CTCDispatch::sendTrackController(CTCSignals &ctc){

    TrackModel::TrainPathInfo route;
    route = findRoute();

    int i = 0;
    for(std::pair<int, TrackModel::SwitchState> val : route.switchStates){
          if(i == 6){
              break;
          }
          tcStates.push_back(val.second);
          i++;
    }

    //ctc.calcRoute(line, tcStates);
    //ctc.setSignal(endblock, speed, authority);
    speed = 30;
    reg.initialize(endblock, speed, authority);

    //alertWaysideSystem(ctc);
    //initializeHW(ctc);
}

CTCMode* CTCDispatch::getCTCMode()
{
    return m;
}

void CTCDispatch::setCTCMode(CTCMode* mode)
{
    m = mode;
}

TrackModel::TrainPathInfo CTCDispatch::findRoute(){
    TrackModel::Route *rte;
    rte = TrackModel::getRoute(line);

    TrackModel::TrainPathInfo path;
    TrackModel::TrackRouter temp(rte);
    path = temp.findPath(0, TrackModel::BLK_NODIR , endblock);

    return path;
}


/*for(std::pair<int, TrackModel::SwitchState> val : route.switchStates){
 *      newvector.push_back(val.second);
 * }
 */

//Take the first 6 switch state values and put them in a vector
//Make sure that they are 0 and 1
//call calcRoute(line, switchVector) of CTCSignals class

