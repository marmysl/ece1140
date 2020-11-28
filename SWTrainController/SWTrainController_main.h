/* Header file for Train Controller */

#ifndef SWTRAINCONTROLLER_H
#define SWTRAINCONTROLLER_H

#include "hw_sw_interfaces.h"
#include  "TrainModel/Train.h"
#include "../CTCOffice/ctcoffice/CTCMode.h"

int init_SWTrainController();

class SWTrainController : public ITrainController
{

public: // TEMPORARILY making everything public for easier implementation
//private:
    int argc;
    //char *argv[];
    CTCMode *mode;
public:
   SWTrainController(CTCMode *m, int, std::string);
   //void calculatePower();
   //void decode(unsigned);
   //void dispatch() override;
};

#endif // SWTRAINCONTROLLER_H
