/* Header file for Train Controller */

#ifndef SWTRAINCONTROLLER_H
#define SWTRAINCONTROLLER_H

#include "TrainCGUI.h"
#include  "TrainModel/Train.h"

int init_SWTrainController(int argc, char *argv[]);

class SWTrainController
{

public: // TEMPORARILY making everything public for easier implementation
//private:
    double power;
    double kp;
    double ki;
    double suggestedSpeed;
    double authority;
    double setpointSpeed;
    unsigned signal;
    int argc;
    char *argv[];
public:
   SWTrainController(int, char*[]);
   void calculatePower();
   void decode(unsigned);
};

#endif // SWTRAINCONTROLLER_H
