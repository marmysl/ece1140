#include "SpeedRegulator.h"
#include <iostream>

SpeedRegulator::SpeedRegulator(Train *ptr)
{
    //CalculatePowerCmd();
    powerCmd = 0;

    //set Setpoint Speed to 0 to begin
    setpointSpeed = 0;

    //Initializes gains to
    Kp = 0.000;
    Ki = 0.000;

    //Set trainModel object to the pointer in the parameters
    trainModel = ptr;

    //Initialize the PID control variables to 0
    uk = 0;
    uk_1 = 0;
    ek = 0;
    ek_1 = 0;

    //Initialize the period T to be 1
    T = 1;

    //Initialize the maxPower to be 120,000 watts
    maxPower = 120000; //this value comes from Flexity 2 Tram datasheet
}
void SpeedRegulator::calcPowerCmd()
{
    //Only calculate a nonzero power while the train has a nonzero authority
    if((trainModel -> sendTrackCircuit() & 0xfffffff) > 0)
    {
        //Call the chooseVcmd() function to ensure there is no stale data for Vcmd
        chooseVcmd();

        //Calculate the values for ek
        ek = Vcmd - trainModel -> getCurrentVelocity();

        //Choose the correct value of uk
        if(powerCmd < maxPower) uk = uk_1 + T*(ek + ek_1);
        else uk = uk_1;

        //Calculate the power command
        powerCmd = (Kp * ek) + (Ki * uk);

        //Sends power command to the trainModel
        trainModel -> setPower(0);

        //Set ek_1 = ek for next power command calculation
        ek_1 = ek;

        //Set uk_1 = ek for next power command calculation
        uk_1 = uk;
    }
    else
    {
        //Set the power command to 0
        powerCmd = 0;

        //Send the power command to the train model
        trainModel -> setPower(powerCmd);
    }
}
double SpeedRegulator::getPowerCmd()
{
    chooseVcmd();
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
    if((setpointSpeed + inc >= 0) && setpointSpeed <= 43 && (setpointSpeed + inc <= 43))
    {
        setpointSpeed += inc;
    }

    //Calculate the power command
    calcPowerCmd();
}
void SpeedRegulator::chooseVcmd()
{
    //If the setpoint speed is greater than or equal to the commanded speed, the lesser of the speeds is the commanded speed
    //The commmanded speed will be Vcmd and will generate the power command
    if(setpointSpeed >= trainModel -> sendTrackCircuit() >> 32) Vcmd = trainModel -> sendTrackCircuit() >> 32;

    //If the commanded speed is greater than the setpoint speed, then the velocity for the power command will be the setpoint speed
    else Vcmd = setpointSpeed;

}
void SpeedRegulator::setKpAndKi(double propGain, double intGain)
{
    Kp = propGain;
    Ki = intGain;
}
double SpeedRegulator::getKp()
{
    return Kp;
}
double SpeedRegulator::getKi()
{
    return Ki;
}
