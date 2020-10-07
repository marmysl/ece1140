#include <iostream>
#include <iomanip>
#include <cstdint>
#include "FailureDetector.hpp"

using namespace std;

FailureDetector :: FailureDetector()
{
	failureCode = 0;
	blockNum = 
}

int FailureDetector :: detectFailure()
{
	return failureCode;
}

std::string FailureDetector::displayFailure()
{
	std::string error = "";
	
	if(failureCode == 1) {
		error = "Broken Rail";
	} else {
		error = "Other Track Error";
	}
	
	return error;
}

void FailureDetector::resetFailure()
{
	failureCode = 0;
}