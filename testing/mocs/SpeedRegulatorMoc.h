#ifndef SPEEDREGULATORMOC_H
#define SPEEDREGULATORMOC_H


#include <cstdint>
#include "TrainMoc.h"

class SpeedRegulatorMoc
{
private:
        TrainMoc *trainModel;
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
        SpeedRegulatorMoc(TrainMoc*);

        //Method to choose proper Vcmd
        void chooseVcmd();

        //Method to inc/dec setpoint speed
        void incSetpointSpeed(double);

        //Calculate powerCmd
        void calcPowerCmd();

        //Set the power command to 0
        void powerCmdZero();

        //Sets Kp and Ki according to engineer input
        void setKpAndKi(double propGain, double intGain);

        //Accessor Methods
        double getSetpointSpeed();
        double getPowerCmd();
        double getVcmd();
        double getKp();
        double getKi();

        //Method to pull the service brake
        void pullServiceBrake();

        //Method to pull the emergency brake
        void pullEmergencyBrake();

};

#endif // SPEEDREGULATORMOC_H
