#include "SWTC.h"


double SWTC :: calculatePower(double currentSpeed)
{
    // calculate power here

    double power = kp + ki / currentSpeed;
    return power;
}


void SWTC :: decode(unsigned signal)  // decodes track circuit into speed & auth //switch to void?
{
    // add stuff here

    //temporary - debugging
    authority = 10.5;
    suggestedSpeed = signal;

}

// Just accessors and mutators below here. Nothin fancy

void SWTC :: setPowerCommand(double newpower)
{
    powerCommand = newpower;
}

double SWTC :: getPowerCommand()
{
    return powerCommand;
}

void SWTC :: setTrainVelocity(double newSpeed)
{
    trainVelocity = newSpeed;
}

double SWTC :: getTrainVelocity()
{
    return trainVelocity;
}

void SWTC :: setKp(double input)
{
    kp = input;
}

double SWTC :: getKp()
{
    return kp;
}

void SWTC :: setKi(double input)
{
    ki = input;
}

double SWTC :: getKi()
{
    return ki;
}
