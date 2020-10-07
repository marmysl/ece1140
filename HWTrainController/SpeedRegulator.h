#ifndef SPEEDREGULATOR_H
#define SPEEDREGULATOR_H

#include <cstdint>

class SpeedRegulator
{
	private:
		double currentSpeed;
		double commandedSpeed;
		double authority;
		double setpointSpeed;
		double powerCmd;
		bool mode;
		double Kp;
		double Ki;
		
	public:

		//Constructor
		SpeedRegulator();

		//Accessor Functions
		double getAuthority();
		double getCurrentSpeed();
		double getCommandedSpeed();
		double getSetpointSpeed();
		double getPowerCmd();
		bool getMode();

		//Driver inputs
		void manualOverride();
		void incSetpointSpeed(double);

		//Calculate powerCmd
		void calculatePowerCmd();

		void decodeTrackSignal(uint16_t trackCircuitSignal);

		void updateValues(uint16_t trackCircuitSignal, bool modeOp, double current_speed);

		void setKpAndKi(double propGain, double intGain);
		double getKp();
		double getKi();

};
#endif