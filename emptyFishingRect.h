#ifndef EMPTYFISHINGRECT_H
#define EMPTYFISHINGRECT_H 
#include <exception>

/**
 * @brief exception class
 * @details exception class to be thrown if 
 * fishing area rectangle top left and bottom right coordinates are equal
 * 
 * @return returns a describing message of what happened
 */
class emptyFishingRect:public std::exception
{
public:
	const char* what() const throw(){
		return "The fishing rectangle needs an area greater than zero.";
	}
		
};


#endif
