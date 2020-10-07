#ifndef FAILUREDETECTOR_H
#define FAILUREDETECTOR_H

#include <string>
#include "Region.cpp"

class FailureDetector
{
private:
	int failureCode;
	int blockNum;
	std::string route;
public:
	FailureDetector();
	int detectFailure();
	std::string displayFailure();
	void resetFailure();
};

#endif