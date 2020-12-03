#include "SWTC.h"
#include "system_main.h"

#include <QTimer>

void SWTC :: calculatePower()
{
    // If the train is in automatic mode, set the setpoint = commanded
    if (mode->getMode() == 0){
        setpointSpeed = commandedSpeed;
    }

    if (serviceBrakeEnabled == false && emergencyBrakeEnabled == false && passengerEBrakeEnabled == false)
    {

        trainVelocity = trainVelocity * 3.6; // convert to km/h

        // Compare setpoint & commanded speed
        if (setpointSpeed <= commandedSpeed){
            speed = setpointSpeed;
        } else {
            speed = commandedSpeed;
        }

        // Ensure speed does not exceed the max speed of the train (70km/h)
        if (speed > 70.00) {speed = 70.00;}

        // Reduce speed if the authority is 1
        if (authority <= 1) { speed = (commandedSpeed / 2); }

        // reduce speed for upcoming station
        if (stationUpcoming == true) { speed = (commandedSpeed / 2); }

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

    // Stop at station, if needed
    stationStop();

    // Limit power to 120kW as per specs
    if (powerCommand > 120000) { powerCommand = 120000; }


    // If authority is 0, set the power command to zero
    if (authority <= 0) {
        powerCommand = 0.0;        
    }
}


void SWTC :: decode(uint64_t decodeSignal)
{
    // Decode
    double decodeSpeed = static_cast<float>(decodeSignal >> 32) / 4096;
    double decodeAuth = decodeSignal & 0xFFFFFFFF;


    setCommandedSpeed(decodeSpeed);
    setAuthority(decodeAuth - 1); // authority is currently 1 larger than it should be. idk
}

void SWTC :: readBeacon(TrackModel::BeaconData beaconData)
{
    nextStation = beaconData.stationName;

    stationUpcoming = beaconData.stationUpcoming;
    stationHere = beaconData.stationHere;
}

void SWTC :: stationStop()
{
    double temp = powerCommand;

    // set power to zero if block has a station
    if (stationHere == true) { powerCommand = 0.0; }

    // if the train has been stopped at a station, check timer & set speed if 60s passed
    if (stationHere == true && hasStoppedAtStation == true){
        if (systemClock->currentTime() >= stationTimerEnd){ // train has been stopped for 60sec
            powerCommand = temp; // keep power command as non-zero
            doorsOpen = false; // close doors
        }
    }

    // if the train has just stopped at a station, set a flag and start a timer and open doors
    if (stationHere == true && trainVelocity == 0.0 && hasStoppedAtStation == false){
        hasStoppedAtStation = true;
        stationTimerStart = systemClock->currentTime();
        stationTimerEnd = stationTimerStart.addSecs(60);
        doorsOpen = true;
    }

    // if the train has left the block with the station, reset station flag.
    if (stationHere == false && hasStoppedAtStation == true) { hasStoppedAtStation = false; }
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

void SWTC :: setPassengerEBrake(bool flag)
{
    passengerEBrakeEnabled = flag;
}

bool SWTC :: getPassengerEBrake()
{
    return passengerEBrakeEnabled;
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

bool SWTC :: getStationHere()
{
    return stationHere;
}

bool SWTC :: getStationUpcoming()
{
    return stationUpcoming;
}

bool SWTC :: getHasStopped()
{
    return hasStoppedAtStation;
}

std::string SWTC :: getNextStation()
{
    return nextStation;
}
