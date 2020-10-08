#include "SpeedRegulator.h"
#include <iostream>

SpeedRegulator::SpeedRegulator(Train *ptr)
{
	std::cout << "speed regulator constructor" << std::endl;

	//calculatePowerCmd();
	powerCmd = 0;

	//set Setpoint Speed to 0 to begin
	setpointSpeed = 0;

	//Initializes gains to 
	Kp = 5.623;
	Ki = 3.124;


	//Set train_model object to the pointer in the parameters
	train_model = ptr;

	//Decode track signal
	decodeTrackSignal();

}
double SpeedRegulator::getAuthority()
{
	return authority;
}
double SpeedRegulator::getCurrentSpeed()
{
	return train_model -> getCurrentVelocity();
}
double SpeedRegulator::getCommandedSpeed()
{
	return commandedSpeed;
}
double SpeedRegulator::getPowerCmd()
{
	calculatePowerCmd();
	return powerCmd;
}
double SpeedRegulator::getSetpointSpeed()
{
	return setpointSpeed;
}
void SpeedRegulator::incSetpointSpeed(double inc)
{
	if((setpointSpeed + inc >= 0) && setpointSpeed <= 43 && (setpointSpeed + inc <= 43))
	{
		setpointSpeed += inc;
	}

}
void SpeedRegulator::calculatePowerCmd()
{
	powerCmd = commandedSpeed * 2;
	train_model -> setPower(powerCmd);
}
void SpeedRegulator::decodeTrackSignal()
{
	commandedSpeed = train_model -> sendTrackCircuit() >> 32;
	authority = train_model -> sendTrackCircuit() & 0xfffffff;
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
