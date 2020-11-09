#ifndef SPEEDREGULATOR_H
#define SPEEDREGULATOR_H

#include <cstdint>
#include "../TrainModel/Train.h"
#include <QObject>
#include <QTimer>
#include <QDateTime>
#include "../CTCOffice/ctcoffice/CTCMode.h"


class SpeedRegulator
{
private:
        Train *trainModel;
        CTCMode *mode;
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
        QDateTime prevTime;
        QDateTime currTime;
        double powers[3];

        //In this class, power is given in Watts

    public:

        //Constructor
        SpeedRegulator(Train*, CTCMode*);

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

        //Method to pull the service brake
        void pullServiceBrake();

        //Method to pull the emergency brake
        void pullEmergencyBrake();

};
#endif
