#ifndef FAILUREDETECTOR_H
#define FAILUREDETECTOR_H

#include<string>

class FailureDetector
{
	private:
		int failureCode;

	public:
		FailureDetector();
		int checkFailure();
		std::string displayFailure();
		void resolveFailure();
};

#endif