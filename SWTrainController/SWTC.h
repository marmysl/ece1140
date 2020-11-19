#ifndef SWTC_H
#define SWTC_H

#include <cstdint>

class SWTC
{
    private:
        double powerCommand = 0;
        double kp;
        double ki;
        double e_k;
        double e_k_1 = 0.0; // initialize e_k-1 to 0 for first sample
        double u_k;
        double u_k_1 = 0.0; // initialize u_k-1 to 0 for first sample
        double T = 1.0; // Sample timing for u_k calculation, also used for timer rate
        double commandedSpeed = 0.0;
        double authority = 0.0;
        double setpointSpeed = 0.0;
        double trainVelocity;
        unsigned signal;
        bool serviceBrakeEnabled = true;
        bool emergencyBrakeEnabled = false;
        bool passengerEBrakeEnabled = false;
        bool doorsOpen = true;
        bool cabinLightsOn = true;
        bool headlightsOn = false;
    public:
        void calculatePower();
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
        double getT();

        void setServiceBrake(bool);
        bool getServiceBrakeFlag();
        void setEmergencyBrake(bool);
        bool getEmergencyBrakeFlag();
        void setPassengerEBrake(bool);
        bool getPassengerEBrake();

        void setCommandedSpeed(double);
        double getCommandedSpeed();
        void setAuthority(double);
        double getAuthority();
        void setSetpointSpeed(double);
        double getSetpointSpeed();

        void setDoorsOpen(bool);
        bool getDoorsOpen();
        void setCabinLightsOn(bool);
        bool getCabinLightsOn();
        void setHeadlightsOn(bool);
        bool getHeadlightsOn();
};

#endif // SWTC_H
