#ifndef SPEEDREGULATOR_H
#define SPEEDREGULATOR_H

#include <cstdint>
#include "Train.h"
#include <time.h>

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
            double powers[3];
            int authority;
            double commandedSpeed;
            bool mode;
            clock_t prevTime;
            clock_t currTime;

    public:

        //Constructor
        SpeedRegulator(Train*, bool);

        //Method to choose proper Vcmd
        void chooseVcmd();

        //Method to inc/dec setpoint speed
        void incSetpointSpeed(double);

        //Calculate powerCmd
        void calcPowerCmd();
        void calcThreePowers();

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
        double getTrackCircuitData();
        double getCommandedSpeed();
        int getAuthority();
        bool getMode();

        //Method to pull the service brake
        void pullServiceBrake();

        //Method to pull the emergency brake
        void pullEmergencyBrake();

        //Method to decode track circuit data
        void decodeTrackCircuit();

        //Method to set the mode of the operation
        void setMode(bool m);

};
#endif
