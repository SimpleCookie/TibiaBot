#include "stdafx.h"
#include "address.h"



address::address(void)
{
	// Player health
	this->playerHealth.push_back(0x00FB104);
	this->playerHealth.push_back(0x4);

	// Player mana
	this->playerMana.push_back(0x00FB104);

	// Battlelist
	this->battleList.push_back(0x001C313C);
	this->battleList.push_back(0x264);
	this->battleList.push_back(0x4);
}



address::~address(void)
{
}

std::vector<DWORD> const address::getPlayerHealth() const{
	return this->playerHealth;
}

std::vector<DWORD> const address::getPlayerMana() const{
	return this->playerMana;
}

std::vector<DWORD> const address::getBattleList() const{
	return this->battleList;
}
