#ifndef SWTC_H
#define SWTC_H

#include <cstdint>

class SWTC
{
    private:
        double powerCommand = 0;
        double kp;
        double ki;
        double commandedSpeed = 0.0;
        double authority = 0.0;
        double setpointSpeed = 0.0;
        double trainVelocity;
        unsigned signal;
        bool serviceBrakeEnabled = false;
        bool emergencyBrakeEnabled = false;
    public:
        double calculatePower(double);
        void decode(uint64_t);

        // Accessors & mutators
        void setPowerCommand(double);
        double getPowerCommand();
        void setTrainVelocity(double);
        double getTrainVelocity();
        void setKp(double);
        double getKp();
        void setKi(double);
        double getKi();
        void setServiceBrake(bool);
        bool getServiceBrakeFlag();
        void setEmergencyBrake(bool);
        bool getEmergencyBrakeFlag();
        void setCommandedSpeed(double);
        double getCommandedSpeed();
        void setAuthority(double);
        double getAuthority();
};

#endif // SWTC_H
