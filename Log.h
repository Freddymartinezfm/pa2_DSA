#ifndef LOG
#define LOG
#include <string>
#include <iostream>

class Log {
public:
	static void m(std::string, std::string);	
};

void Log::m(std::string TAG, std::string mTAG){
	std::cout << TAG << ": " << mTAG << "()" << std::endl;
}


#endif
