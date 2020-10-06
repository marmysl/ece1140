#ifndef TRAINMODELMATH_H
#define TRAINMODELMATH_H


class TrainModelMath
{
public:
    TrainModelMath();
    static double travelledDist(double time, double velocity);
    static double updatePosition(double oldPos, double change);
    static double calcVelocity(double power);

};

#endif // TRAINMODELMATH_H
