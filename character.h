#pragma once
#include "events.h"
#include "magic.h"

class character{
	friend class paladin;
public:
	/**
	 * @brief initiates event object
	 * @details sets event to member event
	 * 
	 * @param event object reference from main
	 */
	character(events &event, magic &_m);

	/**
	 * @brief default constructor
	 * @details default constructor
	 */
	// character();

	/**
	 * @brief default deconstructor
	 * @details default deconstructor
	 */
	~character();

	/**
	 * @brief automatic food eater
	 * @details eats food specified by the user
	 */
	void eatFood(); 

	/**
	 * @brief data for eatFood function
	 * @details prompting the user for information
	 */
	void getFoodData();	

	/**
	 * @brief getter to verify if eatFood is active
	 * @details boolean to determine whether eatFood is active or not
	 * @return true for active or false for inactive
	 */
	bool getEatingFood(); 

	/**
	 * @brief automatic fisher
	 * @details fish at specified area by the user
	 */
	void fisher();

	/**
	 * @brief setter for var eatingFood to param
	 * @details sets bool var eatingFood to param
	 * @param eatingFood True or False
	 */
	void setEatingFood(bool eatingFood);

	/**
	 * @brief get user fishing information
	 * @details prompt user for information about fishingrod, fishing area etc
	 */
	void getFishingData(); 

	/**
	 * @brief getter to verify if fishing is active
	 * @details boolean to determine whether fishing is active or not
	 * @return true for active or false for inactive
	 */
	bool getFishing(); 

	/**
	 * @brief setter for var fishing to param
	 * @details sets bool var fishing to param
	 * @param fishing True or False
	 */
	void setFishing(bool fishing); 


	/**
	 * @brief getter for bool variable
	 * @details to provide user information about active functions eg eatingFood
	 * @return returns a string "enable/disable"
	 */		
	std::string foodState(); 

	/**
	 * @brief getter for bool variables
	 * @details to provide user information about active functions eg fishing
	 * @return returns a string "enable/disable"
	 */		
	std::string fishingState();

	/**
	 * @brief getter for bool variables
	 * @details to provide user information about active functions eg trainingMana
	 * @return returns a string "enable/disable"
	 */		
	std::string manaState(); 

	/**
	 * @brief getter for bool variables
	 * @details to provide user information about active functions eg monkTrainer
	 * @return returns a string "enable/disable"
	 */		
	std::string trainingState();


private:
	magic &_magic; ///< object for the magic class
	bool eatingFood, ///< boolean used in main loop to verify active/inactive functions
	fishing, ///< boolean used in main loop to verify active/inactive functions
	monkTrainer; ///< boolean used in main loop to verify active/inactive functions

	POINT fishingRodPos, ///< coordinates of fishing rod
	topLeft, ///< top left coordinates of the fishing area, used to compute rectangle
	botRight, ///< bottom right coordinates of the fishing area, used to compute rectangle
	foodPos; ///< food coordinates

protected:
	events *event; ///< pointer object for the event class
};


