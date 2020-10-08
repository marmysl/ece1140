#include "Train.h"
//#include <QApplication>
#include <chrono>
#include <cstdint>

#include "TrainModelMath.h"
#include "TrainModelUpdateBlock.h"
using namespace std;

Train::Train(int newNumCars)
{
    numCars = newNumCars;
/*    QApplication a(argc, argv);
    TrainModelUI w;
    uiPtr = &w;
    qapp = &a;
    w.show();
    a.exec();*/
}

/* might need to change this
Train::Train(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrainModel w;
    w.show();
    a.exec();
}
*/

void Train::setPower(double newPower){             //Called by train controller to set power
    //Get current time
    chrono::steady_clock::time_point newTime= chrono::steady_clock::now();

    //Find elapsed time and convert to a double
    auto elapsedTime = newTime - oldTime;
    oldTime = newTime;
    double milliSec = chrono::duration<double, milli>(elapsedTime).count();

    //Find the distance travelled using old velocity
    double distTravelled = TrainModelMath::travelledDist(milliSec, currVel);
    double newPos = TrainModelMath::updatePosition(oldPos, distTravelled);
    //double newPos = 1.0; //temp

    //compare new position to old to see if new block
    if (newPos >= blockDist){
        newPos = newPos - blockDist;
        //update current block and information
        this->updateTrackInfo();
    }
    oldPos = newPos;

    currPower = newPower;
//    uiPtr->updatePower(newPower);
    currVel = TrainModelMath::calcVelocity(newPower);
    //currVel = 2.5; //temp hard coding
}

void Train::updateTrackInfo(){                            //Will update block information
    //update block num
    //update block length
    //send occupancy to Track Model
    blockNum = TrainModelUpdateBlock::updateBlock(blockNum);
    blockDist = TrainModelUpdateBlock::blockLength(blockNum);
    blockGrade = TrainModelUpdateBlock::blockGrade(blockNum);
 //   blockNum = 1;
 //   blockDist = 1.0;
 //   blockGrade = 1.0;
    this->setTrackCircuit(blockNum);
}

//ask about this ?
void Train::setTrackCircuit(int blockNum){                   //Get curr track signal from Track Model when new block
    //get tc info for block
    //assign
    trackCircuitData = TrainModelUpdateBlock::updateTrackCircuit(blockNum);
 //   trackCircuitData = 1;
}

uint64_t Train::sendTrackCircuit(){          //Train controller can call to get curr track signal
    return trackCircuitData;
}


double Train::getCurrentVelocity(){                //Called by train controller to get curr velocity
    return currVel;
}

double Train::getCurrentPosition(){                //will return current position
    return oldPos;
}

