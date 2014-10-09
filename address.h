#pragma once
#include <vector>
#include <Windows.h>

class address
{
public:

	/**
	 * @brief initiate addresses
	 * @details give vectors corresponding offsets
	 */
	address(void);

	/**
	 * @brief default deconstructor
	 * @details default deconstructor
	 */
	~address(void);

	/**
	 * @brief vector that holds address + offsets
	 * @details addressses and offsets to memory locations
	 * @return returns the vector with address + offsets
	 */
	const std::vector<DWORD> getPlayerHealth() const;
	 
	 /**
	 * @brief vector that holds address + offsets
	 * @details addressses and offsets to memory locations
	 * @return returns the vector with address + offsets
	 */
	const std::vector<DWORD> getBattleList() const;
	
	/**
	 * @brief vector that holds address + offsets
	 * @details addressses and offsets to memory locations
	 * @return returns the vector with address + offsets
	 */
	const std::vector<DWORD> getPlayerMana() const;

protected:
	
	std::vector<DWORD> battleList; ///< vector storing memory addresses for battlelist
	std::vector<DWORD> playerHealth; ///< vector storing memory addresses for player health
	std::vector<DWORD> playerMana; ///< vector storing memory addresses for player mana

};



