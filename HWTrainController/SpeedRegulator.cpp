#include "SpeedRegulator.h"

SpeedRegulator::SpeedRegulator(Train *ptr)
{

	//calculatePowerCmd();
	powerCmd = 0;

	//Initializes gains to 
	Kp = 5.623;
	Ki = 3.124;

	//Decode track signal
	decodeTrackSignal();

	//assign the train model
	train_model = ptr;

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
	authority = train_model -> sendTrackCircuit() &= 0xffffffff;
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