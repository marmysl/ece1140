#ifndef SWTC_H
#define SWTC_H

class SWTC
{
    private:
        double power;
        double kp;
        double ki;
        double suggestedSpeed;
        double authority;
        double setpointSpeed;
        unsigned signal;
    public:
        double calculatePower();
        void decode(unsigned);
};

#endif // SWTC_H
