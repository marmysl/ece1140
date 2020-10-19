#ifndef SWTC_H
#define SWTC_H

class SWTC
{
    private:
        double powerCommand = 0;
        double kp;
        double ki;
        double suggestedSpeed;
        double authority;
        double setpointSpeed;
        double trainVelocity;
        unsigned signal;
    public:
        double calculatePower(double);
        void decode(unsigned);

        void setPowerCommand(double);
        double getPowerCommand();
        void setTrainVelocity(double);
        double getTrainVelocity();
        void setKp(double);
        double getKp();
        void setKi(double);
        double getKi();
};

#endif // SWTC_H
