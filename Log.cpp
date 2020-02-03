#include <string>
#include <iostream>

#include "Log.h"


void Log::m(std::string TAG, std::string mTAG){
	std::cout << TAG << ": " << mTAG << "()" << std::endl;
}

