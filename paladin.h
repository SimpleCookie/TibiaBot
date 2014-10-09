#pragma once
#include "character.h"
#include "events.h"


class paladin :
	public character
{
public:

	/**
	 * @brief initiates event object
	 * @details sets event to member event
	 * 
	 * @param event object reference from main
	 */
	paladin(events &event, magic &_m);

	/**
	 * @brief default constructor
	 * @details default constructor
	 */
	paladin();

	/**
	 * @brief default deconstructor
	 * @details default deconstructor
	 */
	~paladin();

	/**
	 * @brief getter for character::monkTrainer
	 * @details returns whether character::monkTrainer is active/inactive
	 * @return true/false
	 */
	bool getMonkTrainer();

	/**
	 * @brief setter for monkTrainer
	 * @details setter for monkTrainer, boolean var used in main to verify for the user whether 
	 * monkTrainer is active/inactive
	 * 
	 * @param monkTrainer boolean var
	 */
	void setMonkTrainer(bool monkTrainer);

	/**
	 * @brief prompts user for information
	 * @details prompts user for information necessary to run the paladinMonkTrainer
	 */
	void getPaladinTrainingData();

	/**
	 * @brief paladin monk trainer
	 * @details attacks a monk, swaps target at low health and picks up spears.
	 */
	void paladinMonkTrainer();

private:
	POINT firstMonkPos, ///< coordinates for monk one
	secondMonkPos, ///< coordinates for monk two
	thirdMonkPos, ///< coordinates for monk three
	spearsHand; ///< position of hand of where to place spears

	int monks, ///< amount of monks 
	spearIntervall; ///< how frequent to pick up new spears

};

