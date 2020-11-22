#ifndef SPEEDREGULATOR_H
#define SPEEDREGULATOR_H

#include <cstdint>
#include "../TrainModel/Train.h"
#include <QObject>
#include <QTimer>
#include <QDateTime>
#include "../CTCOffice/ctcoffice/CTCMode.h"
#include "BeaconDecoder.h"


class SpeedRegulator
{
private:
        Train *trainModel;
        CTCMode *mode;
        BeaconDecoder* beacon;
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
        double commandedSpeed;
        int authority;
        QDateTime prevTime;
        QDateTime currTime;
        int failureCode;

        //In this class, power is given in Watts

    public:

        //Constructor
        SpeedRegulator(Train*, CTCMode*, BeaconDecoder*);

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

        //Method to pull the service brake
        void pullServiceBrake();

        //Method to pull the emergency brake
        void pullEmergencyBrake();

        //Method to set the failure code in the system when a failure is detected
        void setFailureCode(int fc);

        //Function to decode track circuit
        void decodeTrackCircuit();

        //Function to stop at the station
        void stopAtStation();

        //Accessor Methods
        double getSetpointSpeed();
        double getPowerCmd();
        double getVcmd();
        double getKp();
        double getKi();
        int getFailureCode();
        double getCommandedSpeed();
        int getAuthority();

};
#endif
