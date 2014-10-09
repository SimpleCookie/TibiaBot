#include "stdafx.h"
#include "paladin.h"
#include <iostream>

paladin::paladin(events &event, magic &_m):character(event, _m){
}
/*
paladin::paladin()
{
}*/



paladin::~paladin()
{
}


/* Paladin trainer */
void paladin::getPaladinTrainingData(){
	std::cout << "How long intervalls before picking up spears in seconds?" << std::endl << "Enter a valid number: ";
	std::cin >> spearIntervall;
	std::cout << std::endl << "1, 2 or 3 monks: ";
	std::cin >> monks;
	std::cout << std::endl << "hover mouse on a monk and press Enter" << std::endl;
	Sleep(300);
	while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for mouse click
	GetCursorPos(&firstMonkPos); // Get coordinate of fishing rod
	Sleep(rand() % 100 + 200);
	if (monks > 1){
		std::cout << "hover mouse on the Second monk and press Enter" << std::endl;
		Sleep(300);
		while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for mouse click
		GetCursorPos(&secondMonkPos); // Get coordinate of top left rect
		Sleep(rand() % 100 + 200);
	}if (monks > 2){
		std::cout << "hover mouse on the third monk and press Enter" << std::endl;
		Sleep(300);
		while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for mouse click
		GetCursorPos(&thirdMonkPos); // Get coordinate of top left rect
		Sleep(rand() % 100 + 200);
	}
	std::cout << "hover mouse on your hand to refill with spears and press Enter" << std::endl << std::endl;
	Sleep(300);
	while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for mouse click
	GetCursorPos(&spearsHand); // Get coordinate of bottom right rect
	Sleep(rand() % 250 + 100);
	std::cout << "Untarget any monks and set safemode to on!" << std::endl << "Press any key to continue ..." << std::endl;
	Sleep(500);
}


bool paladin::getMonkTrainer(){
	return monkTrainer;
}
void paladin::setMonkTrainer(bool monkTrainer){
	this->monkTrainer = monkTrainer; // Set member variable to param
}
void paladin::paladinMonkTrainer(){
	monkTrainer = !(monkTrainer);
	bool everyOther = true;
	//clock_t this_time = clock();    // time intervalls
	//clock_t last_time = this_time;  // time intervalls
	if (monks == 1)
		event->mouseRightClick(firstMonkPos); // attack training monk
	while (monkTrainer) // If you're not fishing, do it
	{
		event->isPaused();
		//this_time = clock(); // update timer

		event->mutex.lock();
		if (monks == 2){
			if (everyOther){
				event->mouseRightClick(firstMonkPos); // attack target
				Sleep(rand() % spearIntervall + (spearIntervall - 1) * 1500); // For spearIntervall seconds
				event->mouseRightClick(firstMonkPos); // untarget
				Sleep(rand() % 100 + 300);
				event->moveItemStack(firstMonkPos, spearsHand); // refill spears from other monk
				Sleep(rand() % 1000 + 3000);
			}
			else{
				event->mouseRightClick(secondMonkPos); // attack target
				Sleep(rand() % spearIntervall + (spearIntervall - 1) * 1500); // For spearIntervall seconds
				event->mouseRightClick(secondMonkPos); // untarget
				Sleep(rand() % 100 + 300);
				event->moveItemStack(secondMonkPos, spearsHand); // refill spears from other monk
				Sleep(rand() % 1000 + 3000);
			}
		}
		else if (monks == 1)
		{
			Sleep(rand() % spearIntervall + (spearIntervall - 1) * 1000); // For spearIntervall seconds
			event->moveItemStack(firstMonkPos, spearsHand); // refill spears from other monk
		}
		else if (monks == 3)
		{
			/* First monk */
			event->mouseRightClick(firstMonkPos); // attack target
			Sleep(rand() % spearIntervall + (spearIntervall - 1) * 1000); // For spearIntervall seconds
			event->moveItemStack(firstMonkPos, spearsHand); // refill spears from other monk

			/* Second monk */
			event->mouseRightClick(secondMonkPos); // attack target
			Sleep(rand() % spearIntervall + (spearIntervall - 1) * 1000); // For spearIntervall seconds
			event->moveItemStack(secondMonkPos, spearsHand); // refill spears from other monk

			/* Third monk */
			event->mouseRightClick(thirdMonkPos); // attack target
			Sleep(rand() % spearIntervall + (spearIntervall - 1) * 1000); // For spearIntervall seconds
			event->moveItemStack(thirdMonkPos, spearsHand); // refill spears from other monk
		}
		//last_time = this_time; // update timer
		everyOther = !everyOther;
		event->mutex.unlock();

	}
}

