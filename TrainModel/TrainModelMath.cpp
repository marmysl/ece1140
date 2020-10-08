#include "TrainModelMath.h"
#include <chrono>

TrainModelMath::TrainModelMath() {
    //empty constructor
}

double TrainModelMath::travelledDist(double time, double velocity) {
    double dist = velocity * time;
    return dist;
}

double TrainModelMath::updatePosition(double oldPos, double change) {
    return oldPos+change;
}

double TrainModelMath::calcVelocity(double power) {
    return 20;
}

/*
TrainModelMath();
static double travelledDist(double time, double velocity);
static double updatePosition(double oldPos, double change);
static double calcVelocity(double power);
=======
/*
class TrainModelMath
{
    public:
        TrainModelMath()
        {
            //empty constructor
        }

        static double travelledDist(double time, double velocity){
            double dist = velocity * time;
            return dist;
        }

        static double updatePosition(double oldPos, double change){
            return oldPos+change;
        }

        static double calcVelocity(double power){
            return 20;
        }
};
*/

