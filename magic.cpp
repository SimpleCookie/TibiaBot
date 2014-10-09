#include "stdafx.h"
#include "magic.h"
#include "events.h"
#include <iostream>



magic::magic(memoryReading &m, events &e) :memory(m){
	trainingMana = false, makingRunes = false;
	manaRequired = 0;
	event = &e;
}
magic::~magic(){
	delete event;
}

void magic::setManaRequired(int x){
	manaRequired = x;
}

void magic::manaTrainer(){
	if (makingRunes)
		return;
	trainingMana = !trainingMana;
	while (trainingMana){ // If you're not training mana, do it
		event->isPaused();
		if (memory.readMemory(_address.getPlayerMana()) >= manaRequired + rand() % 10 + 5){ // mana req + rand(1-14) mana
			for (int i = 0; i < spellRepeat; i++){
				event->castSpell();
				Sleep(rand() % 1000 + 2000);
			}
		}
		Sleep(20000);
	}
}

void magic::setManaForSpell(){
	std::cout << "Mana to cast spell? Enter a valid number: ";
	std::cin >> manaRequired;
	std::cout << std::endl;
	while (!std::cin){
		std::cout << "Enter a valid number: ";
		std::cin >> manaRequired;
		std::cout << std::endl;
	}
	std::cout << "How many time to cast spell, enter a valid number: ";
	std::cin >> spellRepeat;
	std::cout << std::endl;
	Sleep(200);
}

bool magic::getTrainingMana(){
	return trainingMana;
}
void magic::runeMaker(){
	if (trainingMana) // Only one enabled at a time
		return;
	makingRunes = !makingRunes;
	while (makingRunes){ // If you're not training mana, do it
		event->isPaused();
		if (memory.readMemory(_address.getPlayerMana()) >= manaRequired + rand() % 10 + 1){ // mana req + rand(1-10) mana
			event->mutex.lock();
			for (int i = 0; i < spellRepeat; i++)
			{
				Sleep(rand() % 200 + 400);
				event->moveItem(runeBackpack, handSlot); // move blank to hand
				Sleep(rand() % 180 + 500);
				event->castSpell(); // Cast spell
				Sleep(rand() % 180 + 300);
				for (size_t i = 0; i < emptyBackpackVector.size(); i++)
				{
					event->moveItem(handSlot, emptyBackpackVector[i]); // move blank to empty bps
					Sleep(rand() % 100 + 400);
				}
				Sleep(rand() % 180 + 400);
				event->mouseRightClick(runeBackpack); // try to open new bp
			}
			event->mutex.unlock();
		}
		Sleep(2000);
	}
}

void magic::setRuneMakingData(){
	std::cout << "Hover mouse on any of your empty hand slots and press ENTER" << std::endl;
	Sleep(rand() % 100 + 200);
	while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for mouse click
	GetCursorPos(&handSlot); // Get coordinate of fishing rod
	Sleep(rand() % 100 + 200);

	std::cout << "Hover mouse on the first slot in your backpack of blank runes and press ENTER" << std::endl;
	Sleep(rand() % 100 + 200);
	while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for mouse click
	GetCursorPos(&runeBackpack); // Get coordinate of top left rect
	Sleep(rand() % 100 + 200);

	size_t emptyBackpacks = 1;
	std::cout << "How many empty backpacks do you have?" << std::endl << "Enter a number: ";
	std::cin >> emptyBackpacks;
	std::cout << std::endl << "Hover mouse in all empty backpacks and press ENTER." << std::endl << "Don't move or resize them now." << std::endl << std::endl;
	POINT x;
	for (size_t i = 0; i < emptyBackpacks; i++)
	{
		Sleep(rand() % 100 + 200);
		while (!(GetKeyState(VK_RETURN) & 0x80)){ Sleep(1); } // wait for Enter click
		GetCursorPos(&x);
		emptyBackpackVector.push_back(x); // push coordinates into vector container
		Sleep(rand() % 251 + 100);
		std::cout << i + 1 << " backpacks saved." << std::endl;
	}
	Sleep(300);
}

void magic::setTrainingMana(bool trainingMana){
	this->trainingMana = trainingMana; // Set member variable to param
}

bool magic::getMakingRunes(){
	return makingRunes;
}

void magic::setMakingRunes(bool makingRunes){
	this->makingRunes = makingRunes;
}