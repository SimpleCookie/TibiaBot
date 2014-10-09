// main.cpp : Defines the entry point for the console application.
//
 
#include "stdafx.h"
#include <string>
#include <iostream>
#include <tchar.h>
#include "events.h"
#include "magic.h"
#include <Windows.h>
#include <thread>
#include "address.h"
#include "memoryReading.h"
#include "character.h"
#include "paladin.h"
#include "AccesDeniedError.h"

int main(){
	SetConsoleTitle(_T("Simple"));
    Sleep(100);
    std::string choice;

	try{
		// find windows & create object for class events
		events event(FindWindow( NULL , _T("Tibianic Client") ), FindWindow( NULL , _T("Simple") ));
		address _address;
		memoryReading memory;
		
		magic _magic(memory, event);
		paladin _paladin(event, _magic);
		character _character(event, _magic);
	

		/* Start thread to read inputs & detach from main program */
		std::thread userInputThread( &events::waitForUserInput, std::ref(event));
		userInputThread.detach();
		choice = "\n";
		std::cout << std::endl << "\t -:: Get ready to slack ::-" << std::endl;
		while (choice != "7"){ // Simple user interface
			if (choice != "") {
				std::cout
					<< "Choose option" << std::endl
					<< "[1] -\t " << _character.foodState() << " food eater" << std::endl
					<< "[2] -\t " << _character.manaState() << " mana trainer" << std::endl
					<< "[3] -\t " << _character.fishingState() << " fisher" << std::endl
					<< "[4] -\t " << _character.manaState() << " Rune maker" << std::endl
					<< "[5] -\t Move item stack. Under development" << std::endl
					<< "[6] -\t " << _character.trainingState() << " paladin trainer" << std::endl
					<< "[7] -\t Exit program" << std::endl;
				std::cout << "Your health is ... " << memory.readMemory(_address.getPlayerHealth()) << std::endl;
				std::cout << "Your mana is ... " << memory.readMemory(_address.getPlayerMana()) << std::endl;
			}
			std::getline(std::cin, choice);

			std::cout << std::endl;

			// Choice 1 (Eat food)
			if (choice.find('1') != std::string::npos){
				if (_character.getEatingFood()){ // If stopping, don't ask for info
					_character.setEatingFood(false);
				}
				else {
					_character.getFoodData();
					std::thread eatFoodThread( &character::eatFood, std::ref(_character));
					eatFoodThread.detach();
				}
			// Choice 2 (Mana trainer)
			}else if(choice.find('2') != std::string::npos){   
				if (_magic.getMakingRunes()){
					std::cout << "You must disable rune maker first" << std::endl;
				}
				else if (_magic.getTrainingMana()){ // If stopping, don't ask for info
					_magic.setTrainingMana(false);
				}
				else {
					_magic.setManaForSpell();
					std::thread manaTrainerThread(&magic::manaTrainer, std::ref(_magic));
					manaTrainerThread.detach();
				}


            

			// Choice 3 (Fishing)
			}else if (choice.find('3') != std::string::npos){
				if (_character.getFishing()){ // If stopping, don't ask for info
					_character.setFishing(false);
				}
				else {
					_character.getFishingData();
					std::thread fisherThread(&character::fisher, std::ref(_character));
					fisherThread.detach();
				}
				Sleep(300);
			// Choice 4 (Rune maker)
			}else if(choice.find('4') != std::string::npos){
				if (_magic.getTrainingMana()){
					std::cout << "You must disable mana trainer first" << std::endl;
				}
				else if (_magic.getMakingRunes()){ // If stopping, don't ask for info
					_magic.setMakingRunes(false);
				}
				else {
					_magic.setRuneMakingData();
					_magic.setManaForSpell();
					std::thread runeMakingThread(&magic::runeMaker, std::ref(_magic));
					runeMakingThread.detach();
				}
            

			// Choice 5 (Move stack of items)
			}else if(choice.find('5') != std::string::npos){
				// Still under development
				//std::thread moveItemStackThread(&event::moveItemStack(709, 417, 1450, 247), this); 

			//Paladin monk trainer
			}else if(choice.find('6') != std::string::npos){
				if (_paladin.getMonkTrainer()){ // If stopping, don't ask for info
					_paladin.setMonkTrainer(false);
				}
				else {
					_paladin.getPaladinTrainingData();
					std::thread paladinTrainerThread(&paladin::paladinMonkTrainer, std::ref(_paladin));
					paladinTrainerThread.detach();
				}
				Sleep(300);
			
			//Exit Program
			}else if(choice.find('7') != std::string::npos){
				_character.setEatingFood(false);
				_character.setFishing(false);
				_magic.setMakingRunes(false);
				_magic.setTrainingMana(false);
				event.setReadUserInput(false);
				_paladin.setMonkTrainer(false);
				Sleep(300);
				return 0;

			//Incorrect input
			}else{
				std::cout << "Please choose between [1], [2], [3], [4], [5] and [6]." << std::endl;
			}
		}
	}
	catch (AccesDeniedError &e){
		std::cerr << e.what() << std::endl;
		std::cin.get();
	}
    return 0;
}