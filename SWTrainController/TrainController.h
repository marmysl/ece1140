/* Header file for Train Controller */

#ifndef TRAINCONTROLLER_H
#define TRAINCONTROLLER_H

class TrainController
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
   TrainController(int, char*[]);
   void calculatePower();
   void decode(unsigned);
};

#endif // TRAINCONTROLLER_H
