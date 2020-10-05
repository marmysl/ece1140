/* Header file for Train Controller */

#ifndef TRAINCONTROLLER_H
#define TRAINCONTROLLER_H

class TrainController
{
private:
    double power;
    double kp;
    double ki;
public:
   TrainController();
   double getPower();
   void calculatePower();
   double decode(unsigned);
};

#endif // TRAINCONTROLLER_H
