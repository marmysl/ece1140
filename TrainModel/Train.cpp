#include "Train.h"
#include "TrainModelUI.h"
#include "TrainModelMath.h"
#include <QApplication>
#include <chrono>
using namespace std;

Train::Train(int newNumCars, int argc, char *argv[])
{
    numCars = newNumCars;
    QApplication a(argc, argv);
    TrainModelUI w;
    w.show();
    a.exec();
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

    //compare new position to old to see if new block
    if (newPos >= blockDist){
        newPos = newPos - blockDist;
        //update current block and information
        this->updateTrackInfo();
    }
    oldPos = newPos;

    currPower = newPower;
//    w.updatePower(newPower);
    currVel = TrainModelMath::calcVelocity(newPower);

}

void Train::updateTrackInfo(){                            //Will update block information
    //update block num
    //update block length
    //send occupancy to Track Model
    //getTrackCircuit info on new block
}

//ask about this ?
void Train::getTrackCircuit(int block){                   //Get curr track signal from Track Model when new block
    //get tc info for block
    //assign
}

uint16_t Train::sendTrackCircuit(){          //Train controller can call to get curr track signal
    return trackCircuitData;
}


double Train::getCurrentVelocity(){                //Called by train controller to get curr velocity
    return currVel;
}

double Train::getCurrentPosition(){                //will return current position
    return oldPos;
}

