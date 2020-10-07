#include "FailureDetector.h"

FailureDetector::FailureDetector()
{
	failureCode = 0;
}
int FailureDetector::checkFailure()
{
	//readServer("CheckFailure")
	return failureCode;
}
std::string FailureDetector::displayFailure()
{
	std::string messageToDriver = "";
	if(failureCode == 1)
	{
		messageToDriver = "Warning: Train Engine Failure! \nPull the brake and contact the CTC office";
	}
	else if(failureCode == 2)
	{
		messageToDriver = "Warning: Signal Pickup Failure! \nPull the brake and contact the CTC office";
	}
	else if(failureCode == 3)
	{
		messageToDriver =  "Warning: Train Engine Failure! \nPull the brake and contact the CTC office";
	}
	return messageToDriver;
}
void FailureDetector::resolveFailure()
{
	failureCode = 0;
	//also send a message back to train model saying we are all good now
}