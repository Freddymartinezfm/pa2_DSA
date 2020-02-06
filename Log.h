#include <string>
#include <iostream>


class Log {
private:

public:
	static void m(std::string, std::string);	
};

void Log::m(std::string TAG, std::string mTAG){
	std::cout << TAG << ": " << mTAG << "()" << std::endl;
}



