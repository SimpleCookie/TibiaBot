#include "stdafx.h"
#include "character.h"
#include <iostream>
#include "emptyFishingRect.h"
#include "paladin.h"


character::character(events &event, magic &_m): _magic(_m){
	this->event = &event;

	/* Initiate some booleans */
	eatingFood = false, fishing = false, monkTrainer = false;
}
/*
character::character(){
}*/

character::~character(){
}

/* Begin fishing functions */
bool character::getFishing(){
	return fishing;
}

void character::setFishing(bool fishing){
	this->fishing = fishing; // Set member variable to param
}

void character::getFishingData(){
	std::cout << "Hover mouse over fishingrod at arrowslow and press ENTER" << std::endl;
	Sleep(rand() % 100 + 200);
	while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for mouse click
	GetCursorPos(&fishingRodPos); // Get coordinate of fishing rod
	Sleep(rand() % 100 + 200);

	std::cout << "Hover mouse on the top left rect of the of fishing area and press ENTER" << std::endl;
	Sleep(rand() % 100 + 200);
	while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for mouse click
	GetCursorPos(&topLeft); // Get coordinate of top left rect
	Sleep(rand() % 100 + 200);

	std::cout << "Hover mouse on the bottom right of the rect of fishing area and press ENTER" << std::endl << std::endl;
	Sleep(rand() % 100 + 200);
	while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for mouse click
	GetCursorPos(&botRight); // Get coordinate of bottom right rect
	Sleep(rand() % 251 + 100);
}

void character::fisher(){
	fishing = !fishing;
	while (fishing){ // If you're not fishing, do it
		event->isPaused();
		event->mutex.lock();
		try{
			if (botRight.x == topLeft.x || botRight.y == topLeft.y)
				throw emptyFishingRect();
			POINT tmpCoord;
			tmpCoord.x = rand() % (botRight.x - topLeft.x) + topLeft.x; // Choose random x coordinate inside the rect
			tmpCoord.y = rand() % (botRight.y - topLeft.y) + topLeft.y; // Choose random y coordinate inside the rect

			event->mouseRightClick(fishingRodPos); // Use fishing rod
			Sleep(rand() % 180 + 100);
			event->mouseLeftClick(tmpCoord); // Cast fishing rod
		}
		catch (std::exception &e){
			std::cout << "Division by zero, top left rect cannot be equal to bot right rect." << std::endl << "Error message: " << e.what() << std::endl << std::endl;
			fishing = false;
		}
		event->mutex.unlock();
	}
}
/* End fishing functions */

/* begin food functions */

bool character::getEatingFood(){
	return eatingFood;
}

void character::setEatingFood(bool eatingFood){
	this->eatingFood = eatingFood; // Set member variable to param
}
void character::getFoodData(){
	std::cout << "Hover mouse on your food stack and press ENTER" << std::endl;
	Sleep(500);
	
	while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // Wait for mouse click
	GetCursorPos(&foodPos); // store mouse position in foodPos (right after mouse click)
	Sleep(rand() % 100 + 200);
}

void character::eatFood(){
	eatingFood = !eatingFood;
	clock_t this_time = clock();    // time intervalls
	clock_t last_time = this_time;  // time intervalls
	Sleep(100);
	while (eatingFood){ // If you're not eating food, do it
		event->isPaused();
		this_time = clock(); // update timer
		if (this_time >= last_time + 80 * 1000){ // 80 intervalls
			last_time = this_time; // update timer
			event->mutex.lock();
			for (int i = 0; i < 4; i++)
			{
				event->mouseRightClick(foodPos); // Eat food 4 times
			}
			event->mutex.unlock();
		}
	}
}
/* End food functions */



/* Begin character states */
std::string character::manaState(){
	std::string state;
	if (_magic.trainingMana)
		state = "Disable mana trainer";
	else if (_magic.makingRunes)
		state = "Disable Rune maker";
	else
		state = "Enable";
	return state;
}

std::string character::foodState(){
	std::string state;
	if (eatingFood)
		state = "Disable";
	else
		state = "Enable";
	return state;
}

std::string character::fishingState(){
	std::string state;
	if (fishing)
		state = "Disable";
	else
		state = "Enable";
	return state;
}

std::string character::trainingState(){
	std::string state;
	if (monkTrainer)
		state = "Disable";
	else
		state = "Enable";
	return state;
}

/* End character states*/