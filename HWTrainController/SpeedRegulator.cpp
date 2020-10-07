#include "SpeedRegulator.h"

SpeedRegulator::SpeedRegulator()
{
	//Will be an input from the train model
	currentSpeed = 0;

	//Will be changed once the server is up
	//Values will be recieved from train model 
	mode = 0;

	//calculatePowerCmd();
	powerCmd = 0;

	//Initializes gains to 0
	Kp = 0;
	Ki = 0;

}
double SpeedRegulator::getAuthority()
{
	return authority;
}
double SpeedRegulator::getCurrentSpeed()
{
	return currentSpeed;
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
bool SpeedRegulator::getMode()
{
	return mode;
}
void SpeedRegulator::manualOverride()
{
	//mode = 1;
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
}
void SpeedRegulator::decodeTrackSignal(uint16_t trackCircuitSignal)
{
	commandedSpeed = trackCircuitSignal >> 8;
	authority = trackCircuitSignal &= 0xff;
}
void SpeedRegulator::updateValues(uint16_t trackCircuitSignal, bool modeOp, double current_speed)
{
	//Updates commanded speed and authority
	decodeTrackSignal(trackCircuitSignal);

	//Updates the currentSpeed
	currentSpeed = current_speed;

	//Updates the mode of operation
	mode = modeOp;

	//Updates changes to Kp and Ki
	Kp = getKp();
	Ki = getKi();

	//calculates the power command again
	calculatePowerCmd();

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