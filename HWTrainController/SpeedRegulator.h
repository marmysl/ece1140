#ifndef SPEEDREGULATOR_H
#define SPEEDREGULATOR_H

#include <cstdint>
#include "../TrainModel/Train.h"

class SpeedRegulator
{
	private:
		double commandedSpeed;
		double authority;
		double setpointSpeed;
		double powerCmd;
		double Kp;
		double Ki;
		Train* train_model;
		
	public:

		//Constructor
		SpeedRegulator(*Train ptr);

		//Accessor Functions
		double getAuthority();
		double getCurrentSpeed();
		double getCommandedSpeed();
		double getSetpointSpeed();
		double getPowerCmd();

		//Driver inputs
		void incSetpointSpeed(double);

		//Calculate powerCmd
		void calculatePowerCmd();

		void decodeTrackSignal();

		void setKpAndKi(double propGain, double intGain);
		double getKp();
		double getKi();

};
#endif