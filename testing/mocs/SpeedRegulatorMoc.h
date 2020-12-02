#ifndef SPEEDREGULATORMOC_H
#define SPEEDREGULATORMOC_H


#include <cstdint>
#include <QDateTime>
#include <QtGlobal>
#include "TrainMoc.h"
#include "CTCModeMoc.h"
#include "BeaconDecoderMoc.h"
#include "TrainMoc.h"
#include <QObject>

class SpeedRegulatorMoc : public QObject
{
private:
        TrainMoc *trainModel;
        CTCModeMoc *mode;
        BeaconDecoderMoc* beacon;
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
    public:

        //Constructor
        SpeedRegulatorMoc(TrainMoc*, CTCModeMoc*, BeaconDecoderMoc*);

        //Method to choose proper Vcmd
        void chooseVcmd();

        //Method to inc/dec setpoint speed
        void incSetpointSpeed(double);

        //Calculate powerCmd
        double powerFormula();
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

#endif // SPEEDREGULATORMOC_H
