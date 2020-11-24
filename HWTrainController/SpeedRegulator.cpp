#include "SpeedRegulator.h"
#include <iostream>
#include <cmath>

SpeedRegulator::SpeedRegulator(Train *t, CTCMode *m, BeaconDecoder *b)
{
    //CalculatePowerCmd();
    powerCmd = 0;

    //set Setpoint Speed to 0 to begin
    setpointSpeed = 0;

    //Initializes gains to
    Kp = 0.000;
    Ki = 0.000;

    //Set trainModel object to the pointer in the parameters
    trainModel = t;
    mode = m;
    beacon = b;

    //Initialize the PID control variables to 0
    uk = 0;
    uk_1 = 0;
    ek = 0;
    ek_1 = 0;

    //Initialize the period T to be 0
    T = 0;

    //Initialize the prevTime to be the current time
    prevTime = systemClock -> currentTime();

    //Initialize the maxPower to be 120,000 watts
    maxPower = 120; //this value comes from Flexity2 Tram datasheet

    //Set the failure code to 0 initially
    failureCode = 0;
}
double SpeedRegulator::powerFormula()
{
    //Create a variable to store the power
    double power;

    //Call the chooseVcmd() function to ensure there is no stale data for Vcmd
    chooseVcmd();

    std::cout << "Velocity command: " << Vcmd << std::endl;

    //Calculate the values for ek (convert Vcmd to meters/second)
    ek = (Vcmd*0.277778) - (trainModel -> getCurrentVelocity());

    //Calculate the current time
    currTime = systemClock->currentTime();

    //Find elapsed time and convert to a double
    qint64 change;
    change = prevTime.msecsTo(currTime);
    double elapsedTime = (double)change/1000;

    //Set previous time to current time for next power command calculation
    prevTime = currTime;

    std::cout << "Elapsed Time = " << elapsedTime << std::endl;

    //Set T to the elapsed time
    T = elapsedTime;

    //Choose the correct value of uk
    if(powerCmd <= maxPower) uk = uk_1 + (T/2)*(ek + ek_1);
    else uk = uk_1;

    //Calculate the power command
    power = (Kp * ek) + (Ki * uk);

    //Set ek_1 = ek for next power command calculation
    ek_1 = ek;

    //Set uk_1 = ek for next power command calculation
    uk_1 = uk;

    return power;
}
void SpeedRegulator::calcPowerCmd()
{
    //Only calculate a nonzero power while the train has a nonzero authority and the brake is not being pulled
    if(  (getAuthority() > 0) && (trainModel -> getServiceBrake() != 1) && (trainModel -> getEmergencyBrake() != 1) )
    {
        double power1 = powerFormula();
        double power2 = powerFormula();
        double power3 = powerFormula();

        double avg12 = (power1 + power2) /2;
        double avg13 = (power1 + power3) /2;
        double avg23 = (power2 + power3) /2;

        std::cout << "Difference: " << power1 - power2 << std::endl;

        if(power1 > power2 - 3 && power1 < power2 + 3) powerCmd = avg12;
        else if(power1 > power3 - 3 && power1 < power3 + 3) powerCmd = avg13;
        else if(power3 > power2 - 3 && power3 < power2 + 3) powerCmd = avg23;
        else pullEmergencyBrake();

        //Sends power command to the trainModel (needs conversion kW => W)
        if(powerCmd <= 120 && powerCmd >= -120)
        {
            trainModel -> setPower(powerCmd*1000);
        }
        else if(powerCmd < -120)
        {
            trainModel -> setPower(-120*1000);

        }
        else
        {
            trainModel -> setPower(120*1000);
        }

        std::cout << powerCmd << std::endl;
    }
    else
    {
        powerCmdZero();
    }
}
void SpeedRegulator::powerCmdZero()
{
    //Set the powerCmd var to 0
    powerCmd = 0;

    //Update the train model
    trainModel -> setPower(powerCmd);

    //Set the PID loop variables to the 0 power
    ek_1 = 0;
    uk_1 = 0;

    //Set the setpoint speed to 0
    setpointSpeed = 0;
}
double SpeedRegulator::getPowerCmd()
{
    calcPowerCmd();
    return powerCmd;
}
double SpeedRegulator::getSetpointSpeed()
{
    return setpointSpeed;
}
void SpeedRegulator::incSetpointSpeed(double inc)
{
    //Increment/Decrement the speed of the train according to the joystick input

    //Changes the setpoint speed only if it is within the range of speed as given by the Flexity Tram data sheet and if the emergency or service brakes are being pulled
    if((setpointSpeed + inc*.60934 >= 0) && setpointSpeed <= 70 && (setpointSpeed + inc*.60934 <= 70) && trainModel -> getEmergencyBrake() != 1 && trainModel -> getServiceBrake() !=1 )
    {
        //Add the incremenet as km/h   mi/hr --> km/hr = 1.60934
        setpointSpeed += inc*1.60934;
    }

    //Calculate the power command
    calcPowerCmd();
}
void SpeedRegulator::chooseVcmd()
{
    //If the train is in automatic mode speed is automatically chosen for the train
    if(mode -> getMode() == 0)
    {
        //If a station is upcoming with 10x speed, the commanded speed is 1 mph => 1.60934 kph to help the train slow down fast enough to stop at station
        if(beacon -> getStationUpcoming() && getCommandedSpeed() > 1.60934 && systemClock -> timeScale > 9.00) Vcmd = 1.60934;

        //If a station is upcoming, the speed is 10 mi/hr => 3.21869 km/hr to slow the train down to prepare for stopping
        //Must be this slow so that the train can stop on time in the higher speeds for the 75m blocks
        else if(beacon -> getStationUpcoming() && getCommandedSpeed() > 16.0934) Vcmd = 16.0934;

        //If a station is not upcoming, the speed is simply the commanded speed
        else Vcmd = getCommandedSpeed();
    }

    //If the train is in manual mode, Vmd is chosen differently
    else
    {
        //If the setpoint speed is greater than or equal to the commanded speed, the lesser of the speeds is the commanded speed
        //The commmanded speed will be Vcmd and will generate the power command
        if(setpointSpeed >= getCommandedSpeed()) Vcmd = getCommandedSpeed();

        //If the commanded speed is greater than the setpoint speed, then the velocity for the power command will be the setpoint speed
        else Vcmd = setpointSpeed;
    }

}
void SpeedRegulator::setKpAndKi(double propGain, double intGain)
{
    Kp = propGain*1000;
    Ki = intGain*1000;
}
double SpeedRegulator::getKp()
{
    return Kp;
}
double SpeedRegulator::getKi()
{
    return Ki;
}
void SpeedRegulator::pullServiceBrake()
{
    //Sets the service brake flag in the train model to 1
    trainModel -> setServiceBrake(1);

    //Set the power command to 0
    powerCmdZero();

    //Check for brake failure
    if(trainModel -> getServiceBrake() == 0) setFailureCode(1);
}
void SpeedRegulator::pullEmergencyBrake()
{
    //Sets the emergency brake flag in the train model to 1
    trainModel -> setEmergencyBrake(1);

    //Set the power in the train model to 0
    powerCmdZero();

    //Check for brake failure
    if(trainModel -> getEmergencyBrake() == 0) setFailureCode(1);
}
void SpeedRegulator::setFailureCode(int fc)
{
    //Integer coding system for failures:
    //0 = no failure occurring
    //1 = brake failure
    //2 = engine failure
    //3 = track signal pickup failure
    failureCode = fc;

    //If the failure code is not being set to 0 (no failure), pull emergency brake
    if(failureCode != 0) pullEmergencyBrake();
}
int SpeedRegulator::getFailureCode()
{
    std::cout << "Failure Code: " << failureCode << std::endl;
    return failureCode;
}
void SpeedRegulator::decodeTrackCircuit()
{
    //Check for a track circuit signal pickup failure
    if(trainModel -> sendTrackCircuit() == 0xffffffffffffffff) setFailureCode(3);

    //Decode the track circuit data
    commandedSpeed = (trainModel -> sendTrackCircuit() >> 32) / 4096;
    authority = (trainModel -> sendTrackCircuit() & 0xffffffff) / 4096;
}

double SpeedRegulator::getCommandedSpeed()
{
    //Decode the track circuit
    decodeTrackCircuit();

    //Returns the commanded speed
    return commandedSpeed;
}
int SpeedRegulator::getAuthority()
{
    //Decode the track circuit
    decodeTrackCircuit();

    //Returns the authority
    return authority;
}
