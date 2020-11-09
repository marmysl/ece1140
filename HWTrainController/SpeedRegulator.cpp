#include "SpeedRegulator.h"
#include <iostream>

SpeedRegulator::SpeedRegulator(Train *t, CTCMode *m)
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
}
void SpeedRegulator::calcPowerCmd()
{
    //Only calculate a nonzero power while the train has a nonzero authority and the brake is not being pulled
    if(  ((trainModel -> sendTrackCircuit() & 0xffffffff) > 0) && (trainModel -> getServiceBrake() != 1) && (trainModel -> getEmergencyBrake() != 1) )
    {
        //Call the chooseVcmd() function to ensure there is no stale data for Vcmd
        chooseVcmd();

        //Calculate the values for ek
        ek = Vcmd - trainModel -> getCurrentVelocity();

        //Calculate the value of T:
            //Calculate the current time
            currTime = systemClock -> currentTime();
            std::cout <<"Current Time: " << currTime.toSecsSinceEpoch() << std::endl;
            std::cout <<"Previous Time: " << prevTime.toSecsSinceEpoch() << std::endl;

            //Find the elapsed time and convert to a double
            qint64 elapsedTime = prevTime.msecsTo(currTime);
            std::cout << "Elapsed Time = " << double(elapsedTime/1000) << std::endl;

            //Set T to the elapsed time
            T = (double)elapsedTime/1000;

        //Choose the correct value of uk
        if(powerCmd < maxPower) uk = uk_1 + (T/2)*(ek + ek_1);
        else uk = uk_1;

        //Calculate the power command
        powerCmd = (Kp * ek) + (Ki * uk);
        trainModel -> setPower(powerCmd);

        //Sends power command to the trainModel
        if(powerCmd < 120000) trainModel -> setPower(powerCmd);
        else
        {
            powerCmd = 120000;
            trainModel -> setPower(powerCmd);
        }

        //Set ek_1 = ek for next power command calculation
        ek_1 = ek;

        //Set uk_1 = ek for next power command calculation
        uk_1 = uk;

        //Set previous time to current time for next power command calculation
        prevTime = currTime;
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
    if((setpointSpeed + inc >= 0) && setpointSpeed <= 43 && (setpointSpeed + inc <= 43) && trainModel -> getEmergencyBrake() != 1 && trainModel -> getServiceBrake() !=1 )
    {
        setpointSpeed += inc;
    }

    //Calculate the power command
    calcPowerCmd();
}
void SpeedRegulator::chooseVcmd()
{
    //If the train is in automatic mode, speed is automatically set to the commanded speed
    if(mode -> getMode() == 0) Vcmd = trainModel -> sendTrackCircuit() >> 32;

    //If the train is in manual mode, Vmd is chosen differently
    else
    {
        //If the setpoint speed is greater than or equal to the commanded speed, the lesser of the speeds is the commanded speed
        //The commmanded speed will be Vcmd and will generate the power command
        if(setpointSpeed >= trainModel -> sendTrackCircuit() >> 32) Vcmd = trainModel -> sendTrackCircuit() >> 32;

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
}
void SpeedRegulator::pullEmergencyBrake()
{
    //Sets the emergency brake flag in the train model to 1
    trainModel -> setEmergencyBrake(1);

    //Set the power in the train model to 0
    powerCmdZero();
}
