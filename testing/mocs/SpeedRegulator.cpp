#include "SpeedRegulator.h"
#include <iostream>

SpeedRegulator::SpeedRegulator(Train *t, bool m)
{
    //CalculatePowerCmd();
    powerCmd = 0;

    //set Setpoint Speed to 0 to begin
    setpointSpeed = 0;

    //Initializes gains to
    Kp = 0.000;
    Ki = 0.000;

    //Initialize Vcmd to be 0
    Vcmd = 0;

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

    //Initialize the maxPower to be 120,000 watts
    maxPower = 120000; //this value comes from Flexity 2 Tram datasheet

    //Initialize the power commands to 0
    powers[0] = 0;
    powers[1] = 0;
    powers[2] = 0;

    //Pull the service brake until train starts moving
    pullServiceBrake();

    //Initialize the mode to be 0
    mode = m;

    //Decode the track circuit
    decodeTrackCircuit();
}
void SpeedRegulator::calcThreePowers()
{
    //CALCULATE POWER 0
    //Only calculate a nonzero power while the train has a nonzero authority and the brake is not being pulled
    if(  (getAuthority() > 0) && (trainModel -> getServiceBrake() != 1) && (trainModel -> getEmergencyBrake() != 1) )
    {
        //Call the chooseVcmd() function to ensure there is no stale data for Vcmd
        chooseVcmd();

        //Calculate the values for ek
        ek = Vcmd - trainModel -> getCurrentVelocity();

        //Calculate the value of T:
            //Calculate the current time
            currTime = clock();

            //Find the elapsed time and convert to a double
            int elapsedTime = currTime/CLOCKS_PER_SEC - prevTime/CLOCKS_PER_SEC;
            std::cout << "Elapsed Time = " << double(elapsedTime) << std::endl;

            //Set T to the elapsed time
            T = (double)elapsedTime;

        //Choose the correct value of uk
        if(powerCmd < maxPower) uk = uk_1 + (T/2)*(ek + ek_1);
        else uk = uk_1;

        //Calculate the power command
        double power0 = (Kp * ek) + (Ki * uk);

        //Ensures the power command is not larger than the capacity of the train
        if(powerCmd <= 120000 && powerCmd >= -120000) powers[0] = power0;
        else if(powerCmd <= -120000) powers[0] = -120000;
        else powers[0] = 120000;
    }
    else powers[0] = 0;

    //CALCULATE POWER 1
    //Only calculate a nonzero power while the train has a nonzero authority and the brake is not being pulled
    if(  (getAuthority() > 0) && (trainModel -> getServiceBrake() != 1) && (trainModel -> getEmergencyBrake() != 1) )
    {
        //Call the chooseVcmd() function to ensure there is no stale data for Vcmd
        chooseVcmd();

        //Calculate the values for ek
        ek = Vcmd - trainModel -> getCurrentVelocity()/1000;

        //Calculate the value of T:
            //Calculate the current time
            currTime = clock();

            //Find the elapsed time and convert to a double
            int elapsedTime = currTime/CLOCKS_PER_SEC - prevTime/CLOCKS_PER_SEC;
            std::cout << "Elapsed Time = " << double(elapsedTime) << std::endl;

            //Set T to the elapsed time
            T = (double)elapsedTime;

        //Choose the correct value of uk
        if(powerCmd < maxPower) uk = uk_1 + (T/2)*(ek + ek_1);
        else uk = uk_1;

        //Calculate the power command
        double power1 = (Kp * ek) + (Ki * uk);

        //Ensures the power command is not larger than the capacity of the train
        if(powerCmd <= 120000 && powerCmd >= -120000) powers[1] = power1;
        else if(powerCmd <= -120000) powers[1] = -120000;
        else powers[1] = 120000;
    }
    else powers[1] = 0;

    //CALCULATE POWER 1
    //Only calculate a nonzero power while the train has a nonzero authority and the brake is not being pulled
    if(  (getCommandedSpeed() > 0) && (trainModel -> getServiceBrake() != 1) && (trainModel -> getEmergencyBrake() != 1) )
    {
        //Call the chooseVcmd() function to ensure there is no stale data for Vcmd
        chooseVcmd();

        //Calculate the values for ek
        ek = Vcmd - trainModel -> getCurrentVelocity();

        //Calculate the value of T:
            //Calculate the current time
            currTime = clock();

            //Find the elapsed time and convert to a double
            int elapsedTime = currTime/CLOCKS_PER_SEC - prevTime/CLOCKS_PER_SEC;
            std::cout << "Elapsed Time = " << double(elapsedTime) << std::endl;

            //Set T to the elapsed time
            T = (double)elapsedTime;

        //Choose the correct value of uk
        if(powerCmd < maxPower) uk = uk_1 + (T/2)*(ek + ek_1);
        else uk = uk_1;

        //Calculate the power command
        double power2 = (Kp * ek) + (Ki * uk);

        //Ensures the power command is not larger than the capacity of the train
        if(powerCmd <= 120000 && powerCmd >= -120000) powers[2] = power2;
        else if(powerCmd <= -120000) powers[2] = -120000;
        else powers[2] = 120000;
    }
    else powers[2] = 0;

    //Set ek_1 = ek for next power command calculation
    ek_1 = ek;

    //Set uk_1 = ek for next power command calculation
    uk_1 = uk;

    //Set previous time to current time for next power command calculation
    prevTime = currTime;
}
void SpeedRegulator::calcPowerCmd()
{
    //Obtain three power values to compare
    calcThreePowers();

    //Ensure that at least 2/3 are the same/similar and avg the two to send as power command
    if( (powers[0] == 0) && (powers[1] == 0) && (powers[2] == 0) ) powerCmdZero();
    else if(powers[0] < (powers[1] + 100) && powers[0] > (powers[1] - 100))
    {
        powerCmd = (powers[1] = powers[0])/2;
        trainModel -> setPower(powerCmd);
    }
    else if(powers[2] < powers[1] + 100 && powers[2] > powers[1] - 100)
    {
        powerCmd = (powers[1] = powers[2])/2;
        trainModel -> setPower(powerCmd);
    }
    else if(powers[2] < powers[0] + 100 && powers[2] > powers[0] - 100)
    {
        powerCmd = (powers[2] = powers[0])/2;
        trainModel -> setPower(powerCmd);
    }
    else pullEmergencyBrake();
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
    if(mode == 0 && getCommandedSpeed() < 43)  Vcmd = getCommandedSpeed();
    else if(mode == 0 && getCommandedSpeed() >= 43) Vcmd = 43;

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
}
void SpeedRegulator::pullEmergencyBrake()
{
    //Sets the emergency brake flag in the train model to 1
    trainModel -> setEmergencyBrake(1);

    //Set the power in the train model to 0
    powerCmdZero();
}
void SpeedRegulator::decodeTrackCircuit()
{
    authority = (trainModel -> sendTrackCircuit() & 0xffffffff) / 4096;
    commandedSpeed = (trainModel -> sendTrackCircuit() >> 32) / 4096;
}

int SpeedRegulator::getAuthority()
{
    decodeTrackCircuit();
    return authority;
}
double SpeedRegulator::getCommandedSpeed()
{
    decodeTrackCircuit();
    return commandedSpeed;
}
bool SpeedRegulator::getMode()
{
    return mode;
}
void SpeedRegulator::setMode(bool m)
{
    mode = m;
}
double SpeedRegulator::getVcmd()
{
    return Vcmd;
}
