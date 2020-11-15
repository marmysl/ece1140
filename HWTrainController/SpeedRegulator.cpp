#include "SpeedRegulator.h"
#include <iostream>

SpeedRegulator::SpeedRegulator(Train *t, BeaconDecoder* b, CTCMode *m)
{
    //CalculatePowerCmd();
    powerCmd = 0;

    //set Setpoint Speed to 0 to begin
    setpointSpeed = 0;

    //Initializes gains to
    Kp = 0.000;
    Ki = 0.000;

    //Set pointer objects
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
    maxPower = 120000; //this value comes from Flexity 2 Tram datasheet

    //Initialize failure code to be 0
    failureCode = 0;

}
void SpeedRegulator::calcPowerCmd()
{
    //Only calculate a nonzero power while the train has a nonzero authority and the brake is not being pulled
    if(  ((getAuthority()) > 0) && (trainModel -> getServiceBrake() != 1) && (trainModel -> getEmergencyBrake() != 1) && (beacon -> getStationUpcoming() == 0))
    {
        //Call the chooseVcmd() function to ensure there is no stale data for Vcmd
        chooseVcmd();

        //Calculate the values for ek (convert Vcmd to meters/second)
        ek = (Vcmd*0.277778) - (trainModel -> getCurrentVelocity());

        //Calculate the value of T:
            //Calculate the current time
            //Find the elapsed time and convert to a double
            qint64 elapsedTime = prevTime.msecsTo(currTime);

            currTime = systemClock->currentTime();

            //Find elapsed time and convert to a double
            qint64 change;
            change = prevTime.msecsTo(currTime);
            elapsedTime = (double)change/1000;

            //Set previous time to current time for next power command calculation
            prevTime = currTime;

            std::cout << "Elapsed Time = " << elapsedTime << std::endl;

            //Set T to the elapsed time
            T = elapsedTime;

        //Choose the correct value of uk
        if(powerCmd <= maxPower) uk = uk_1 + (T/2)*(ek + ek_1);
        else uk = uk_1;

        //Calculate the power command
        powerCmd = (Kp * ek) + (Ki * uk);
        trainModel -> setPower(powerCmd);
        if(trainModel -> getPower() == 0) setFailureCode(2);

        //Sends power command to the trainModel
        if(powerCmd < 120) trainModel -> setPower(powerCmd);
        else
        {
            powerCmd = 120;
            trainModel -> setPower(powerCmd);
            if(trainModel -> getPower() == 0) setFailureCode(2);
        }

        //Set ek_1 = ek for next power command calculation
        ek_1 = ek;

        //Set uk_1 = ek for next power command calculation
        uk_1 = uk;

    }
    else
    {
        powerCmdZero();
    }
}

void SpeedRegulator::stopAtStation()
{

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
    if((setpointSpeed + inc >= 0) && setpointSpeed <= 43.496 && (setpointSpeed + inc <= 43.496) && trainModel -> getEmergencyBrake() != 1 && trainModel -> getServiceBrake() !=1 )
    {
        //Add the incremenet as km/h   mi/hr --> km/hr = 1.60934
        setpointSpeed += inc*1.60934;
    }

    //Calculate the power command
    calcPowerCmd();
}
void SpeedRegulator::chooseVcmd()
{
    //Choosing Vcmd in automatic mode
    if(mode -> getMode() == 0)
    {
        //If a station is upcoming, Vcmd will be 10 mi/hr => 16.0934 km/hr in order to slow down and prepare to stop (if the setpoint speed and commandedspeed are greater than 10 mph
        if(beacon -> getStationUpcoming() == 1 && getSetpointSpeed() > 16.0934 && getCommandedSpeed() > 16.0934 ) Vcmd = 16.0934;

        //Else if no station is upcoming, Vcmd will be the commanded speed
        else Vcmd = getCommandedSpeed();
    }

    //If the train is in manual mode, Vmd is chosen differently
    else
    {
        //If a station is upcoming, the setpoint speed is automatically adjusted to 10 mi/hr => 16.0934 km/hr, so the train will travel at this speed unless the commanded speed is lower
        if(beacon -> getStationUpcoming() == 1) Vcmd = 16.0934;
        else
        {
            //If setpoint speed is greater than commanded Speed, then Vcmd is the commandedSpeed
            if(setpointSpeed >= getCommandedSpeed()) Vcmd = getCommandedSpeed();

            //If the commanded speed is greater than the setpoint speed, then the velocity for the power command will be the setpoint speed
            else Vcmd = setpointSpeed;
        }
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
}
int SpeedRegulator::getFailureCode()
{
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
