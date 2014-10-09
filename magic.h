#pragma once
#include "address.h"
#include "memoryReading.h"



class events;
class magic
{
	friend class character;
	friend class events;
public:

	/**
	 * @brief initiate variables and allocate for event object
	 * @details sets booleans to false, manaRequired to 0 and allocates memory required
	 * for event pointer object
	 */
	magic(memoryReading &m, events &e);

	/**
	 * @brief prevents dingling pointer
	 * @details deletes event pointer
	 */
	~magic();


	/**
	 * @brief prompts user for required mana
	 * @details promps user for an integrer, the required mana to cast a spell
	 * and how many times to cast the spell
	 */
	void setManaForSpell();	

	/**
	 * @brief sets the required mana to param
	 * @details setter for required mana, rather useless function
	 * 
	 * @param x integrer representing the amount of mana to cast spell
	 */
	void setManaRequired(int x);

	/**
	 * @brief getter for trainingMana
	 * @details getter to verify for the user whether trainingMana is active/inactive
	 * @return returns true/false
	 */
	bool getTrainingMana(); 

	/**
	 * @brief setter for trainingMana variable
	 * @details setter for trainingMana
	 * 
	 * @param trainingMana true/false
	 */
	void setTrainingMana(bool trainingMana);

	/**
	 * @brief automatic mana trainer
	 * @details automatic mana trainer, casts a spell if mana is more than manaRequired,
	 * else sleeps till manaRequired is less than current mana
	 */
	void manaTrainer();	

	/**
	 * @brief automatic rune maker
	 * @details automatic rune maker that makes rune with simulated mouse movements and mouse clicks,
	 * user information required.
	 */
	void runeMaker();

	/**
	 * @brief retrieves information
	 * @details Prompts user for coordinates of "blank runes"
	 */
	void setRuneMakingData();

	/**
	 * @brief getter for makingRunes
	 * @details getter to verify for the user whether makingRunes is active/inactive
	 * @return true/false
	 */
	bool getMakingRunes();

	/**
	 * @brief setter for makingRunes
	 * @details sets MakingRunes to true/false
	 * 
	 * @param makingRunes boolean true/false
	 */
	void setMakingRunes(bool makingRunes); 


private:
	address _address; ///< object for the address class
	memoryReading &memory; ///< object for the memory reading class
	events *event; ///< object pointer for the event class


	std::vector <POINT> emptyBackpackVector; ///< backpack/s to put runes from and into

	// Where to put blank rune when making a rune
	POINT handSlot, ///< coordinates of hand to know where to put blank runes to/from
	runeBackpack; ///< coordinates of backpack to know where to place runes to/from

	// Mana required for spell and how many times to cast it
	int manaRequired, ///< Mana required to cast spell
	spellRepeat; ///< Times to repeat the casted spell

	// Training mana (repeatedly casting useless spells) or making runes
	bool trainingMana, ///< boolean to verify if manaTrainer is active
	makingRunes; ///< boolean to verify if runeMaker is active
};

