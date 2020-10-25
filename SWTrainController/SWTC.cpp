#include "SWTC.h"


void SWTC :: calculatePower()
{
    double speed;
    // Compare setpoint & commanded speed
    if (setpointSpeed <= commandedSpeed){
        speed = setpointSpeed;
    } else {
        speed = commandedSpeed;
    }

    double power = kp + ki / speed;

    if (speed == 0) {power = 0;}

    setPowerCommand(power);
}


void SWTC :: decode(uint64_t decodeSignal)  // decodes track circuit into speed & auth //switch to void?
{
    double decodeSpeed = decodeSignal >> 32;
    double decodeAuth = decodeSignal & 0xfffffff;


    // TEMP: Hard coding commanded speed and authority since track controller gives 0
    decodeSpeed = 25.0;
    decodeAuth = 45.0;


    setCommandedSpeed(decodeSpeed);
    setAuthority(decodeAuth);

}

// ------------------------------------------------------------ Just accessors and mutators below here. Nothin fancy

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

void SWTC :: setServiceBrake(bool flag)
{
    serviceBrakeEnabled = flag;
}

bool SWTC :: getServiceBrakeFlag()
{
    return serviceBrakeEnabled;
}

void SWTC :: setEmergencyBrake(bool flag)
{
    emergencyBrakeEnabled = flag;
}

bool SWTC :: getEmergencyBrakeFlag()
{
    return emergencyBrakeEnabled;
}

void SWTC :: setCommandedSpeed(double speed)
{
    commandedSpeed = speed;
}

double SWTC :: getCommandedSpeed()
{
    return commandedSpeed;
}

void SWTC :: setAuthority(double newAuth)
{
    authority = newAuth;
}

double SWTC :: getAuthority()
{
    return authority;
}

void SWTC :: setSetpointSpeed(double speed)
{
    setpointSpeed = speed;
}
double SWTC :: getSetpointSpeed()
{
    return setpointSpeed;
}
