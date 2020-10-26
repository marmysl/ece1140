#ifndef SPEEDREGULATOR_H
#define SPEEDREGULATOR_H

#include <cstdint>
#include "../TrainModel/Train.h"

class SpeedRegulator
{
private:
        Train *trainModel;
        double setpointSpeed;
        double Vcmd;
        double powerCmd;
        double Kp;
        double Ki;
        double uk;
        double uk_1;
        double ek;
        double ek_1;
        double T;
        double maxPower;

        //In this class, power is given in Watts

    public:

        //Constructor
        SpeedRegulator(Train*);

        //Method to choose proper Vcmd
        void chooseVcmd();

        //Method to inc/dec setpoint speed
        void incSetpointSpeed(double);

        //Calculate powerCmd
        void calcPowerCmd();

        //Sets Kp and Ki according to engineer input
        void setKpAndKi(double propGain, double intGain);

        //Accessor Methods
        double getSetpointSpeed();
        double getPowerCmd();
        double getVcmd();
        double getKp();
        double getKi();

};
#endif
