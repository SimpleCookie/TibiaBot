#ifndef EVENTS
#define EVENTS
#include <string>
#include <Windows.h>
#include <mutex>
#include "memoryReading.h"
#include "address.h"
#include "vector"


class magic;
class events:public memoryReading{
	friend class magic;
	friend class character;
	friend class paladin;
public:
    /**
     * @brief default constructor
     * @details default constructor
     */
	~events();
    
    /**
     * @brief default deconstructor
     * @details default deconstructor
     */
    events(){}
	
	/**
     * @brief sets bot window topmost and initiate booleans
     * @details sets the bot window to the most front (top most) 
     * and initiate booleans with value false
     */
    events(HWND hWnd, HWND Bot);

    /**
     * @brief move items from source to destination
     * @details move items from (x1,y1) to (x2,y2) 
     * by press down mouse left -> hold CTRL -> drag -> let go of CTRL + mouse click
     * 
     * @param from source coordinates
     * @param to destination coordinates
     */
	void moveItemStack(POINT from, POINT to);

	/**
	 * @brief setter for boolean readUserInput
	 * @details Sets readUserInput to true/false
	 * 
	 * @param readUserInput boolean private member
	 */
	void setReadUserInput(bool readUserInput); 

	/**
	 * @brief function waiting for user to hit pause/break key
	 * @details temporary pauses the program when pause/break key is hit
	 */
	void waitForUserInput();


	std::mutex mutex; ///< mutex to prevent mutual exclusion
	bool pauseBot; ///< boolean to verify if the bot has been paused

private:
		
	/**
	 * @brief if paused, this function will sleep
	 * @details this function sleeps the program until unpaused
	 */
	void isPaused(); 

	/**
	 * @brief simulates a predefined hotkey to cast a spell
	 * @details casts a spell by pressing a predefined key, so called "hotkey", eg F10.
	 */
	void castSpell(); 

	/**
	 * @brief simulates mouse left click
	 * @details simulates a left mouse click at chosen coordinates
	 * 
	 * @param coord coordinates to be clicked at
	 */
	void mouseLeftClick(POINT Coord); 

	/**
	 * @brief simulates mouse right click
	 * @details simulates a right mouse click at chosen coordinates
	 * 
	 * @param coord coordinates to be clicked at
	 */
	void mouseRightClick(POINT coord); 

	/**
	 * @brief move items from source to destination
	 * @details move items from (x1,y1) to (x2,y2)
	 * by mouse left down -> drag -> mouse left up
	 * 
	 * @param from source coordinates
	 * @param to destination coordinates
	 */
	void moveItem(POINT from, POINT to);

	/**
	 * @brief checks if a key is pressed
	 * @details bitwise or operation to see whether a key is pressed
	 * 
	 * @param char ascii value for key to be compared
	 * @return returns true/false
	 */
	bool keyIsPressed ( unsigned char k ); 
	
	bool readUserInput; ///< boolean to wait for user input
	
	/* Handles */
    HWND hWnd, ///< handle for the tibiaclient
    Bot; ///< handle for the bot client
};

#endif 
/* events.H */
