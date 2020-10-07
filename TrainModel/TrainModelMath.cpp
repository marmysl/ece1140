#include "TrainModelMath.h"
#include <chrono>
using namespace std::chrono;

TrainModelMath::TrainModelMath()
{
    //empty constructor
}

double TrainModelMath::travelledDist(double time, double velocity){
    double dist = velocity * time;
    return dist;
}

double TrainModelMath::updatePosition(double oldPos, double change){
    return oldPos+change;
}

double TrainModelMath::calcVelocity(double power){
    return 20;
}
