#pragma once
#include <sstream>
#include <exception>

/**
* @brief exception class
* @details exception class to be thrown if
* access is denied when trying to open the process
*
* @return returns a describing message of what happened
*/
class AccesDeniedError :public std::exception
{
public:
	AccesDeniedError(int E) :Error(E){
		std::stringstream ss;
		ss << "Error message: " << Error << ". Memory reading failed." << std::endl;
		msg = ss.str();
	}
	const char* what() const throw(){
		return msg.c_str();
	}
private:
	std::string msg;
	int Error;
};


