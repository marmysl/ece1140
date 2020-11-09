#include <iostream>
#include <iomanip>
#include <cstdint>
#include "FailureDetector.hpp"

using namespace std;

FailureDetector :: FailureDetector()
{
	failureCode = 0;
    //blockNum = getCurrentBlock();
    //route = getRoute();
	cout << "\nin failure detector - block num is " << blockNum << endl;
}

int FailureDetector :: detectFailure()
{
    //failureCode = TrackModel::getFaults(route, blockNum);

	if (failureCode != 0) {
        //displayFailure();
	}

	return failureCode;
}

std::string FailureDetector::displayFailure()
{
	std::string error = "";
	
	if (failureCode == 1) {
		error = "Warning: Broken Rail";
	} else if (failureCode == 2) {
		error = "Warning: Circuit Fail";
	} else if (failureCode == 3) {
		error = "Warning: Power Fail";
	}
	
	return error;
}

void FailureDetector::resetFailure()
{
	failureCode = 0;
}
