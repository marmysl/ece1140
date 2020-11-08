#include "SWTC.h"


void SWTC :: calculatePower()
{
    // Only set the power when the brake flags are off

    if (serviceBrakeEnabled == false && emergencyBrakeEnabled == false)
    {
        // Determine speed to set to: Setpoint or Commanded
        // (do not regulate to setpoint if past commanded)

        double speed; // speed we are regulating to

        // Compare setpoint & commanded speed
        if (setpointSpeed <= commandedSpeed){
            speed = setpointSpeed;
        } else {
            speed = commandedSpeed;
        }

        // Safety measure in case garbage commanded speed or train velocity are sent
        if (speed < 0) {speed = 0;}
        if (trainVelocity < 0) {trainVelocity = 0;}

        // Calculate e_k
        e_k = speed - trainVelocity;

        // Calculate u_k
        u_k = u_k_1 + (T / 2) * (e_k - e_k_1);

        // Set e_k to e_k_1 for next sample
        e_k_1 = e_k;

        // Calculate p_cmd
        powerCommand = kp * e_k + ki * u_k;
    }

    // If authority is 0, set the power command to zero and the service brake flag on.
    if ((authority = 0)) {
        powerCommand = 0.0;
    }
}


void SWTC :: decode(uint64_t decodeSignal)
{
    // Decode
    double decodeSpeed = decodeSignal >> 32;
    double decodeAuth = decodeSignal & 0xfffffff;


    // TEMP: Hard coding commanded speed and authority until we have track controllers
    // decodeSpeed = 25.0;
    // decodeAuth = 1.0;


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

void SWTC :: setDoorsOpen(bool i)
{
    doorsOpen = i;
}

bool SWTC :: getDoorsOpen()
{
    return doorsOpen;
}

void SWTC :: setCabinLightsOn(bool i)
{
    cabinLightsOn = i;
}

bool SWTC :: getCabinLightsOn()
{
    return cabinLightsOn;
}

void SWTC :: setHeadlightsOn(bool i)
{
    headlightsOn = i;
}

bool SWTC :: getHeadlightsOn()
{
    return headlightsOn;
}

double SWTC :: getT()
{
    return T;
}
