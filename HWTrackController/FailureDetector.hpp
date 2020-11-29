#ifndef FAILUREDETECTOR_H
#define FAILUREDETECTOR_H

#include <string>
#include "Region.hpp"

class FailureDetector : private Region
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