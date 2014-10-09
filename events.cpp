#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include "events.h"
#include "magic.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>
#include "emptyFishingRect.h"
#include <chrono>
#include <thread>


events::events(HWND hWnd, HWND Bot):hWnd(hWnd), Bot(Bot){
    SetWindowPos(Bot, HWND_TOPMOST, 0, 0, 150, 50, SWP_NOMOVE|SWP_NOSIZE);

	/* Initiate some booleans */
	pauseBot = false, readUserInput = true;
}
events::~events(){
}

void events::mouseLeftClick(POINT coord){ 
    SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(coord.x, coord.y-20)); // left mouseclick down (windows.h)
    Sleep(100); 
    SendMessage(hWnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(coord.x, coord.y-20)); // left mouseclick up (windows.h)
    Sleep(300);
}

void events::moveItem(POINT from, POINT to){
	POINT tmp;
	GetCursorPos(&tmp);
	SetPhysicalCursorPos(tmp.x+1, tmp.y+1);
    SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(from.x, from.y-20)); // left mouseclick down (windows.h)
    SetPhysicalCursorPos(tmp.x-1, tmp.y-1);
	Sleep(200);
	GetCursorPos(&tmp);
	SetPhysicalCursorPos(tmp.x+1, tmp.y+1);
    SendMessage(hWnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(to.x, to.y-20)); // left mouseclick up (windows.h)
    SetPhysicalCursorPos(tmp.x+1, tmp.y-1);
	Sleep(200);
}




void events::mouseRightClick(POINT coord){ 
    SendMessage(hWnd, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(coord.x, coord.y-20)); // right mouseclick down (windows.h)
    Sleep(rand()%180+100); 
    SendMessage(hWnd, WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(coord.x, coord.y-20)); // right mouseclick up (windows.h)
    Sleep(rand()%180+100); 
}

void events::moveItemStack(POINT from, POINT to){
	SendMessage(hWnd, WM_SYSKEYDOWN, VK_CONTROL, 0); // Press down CTRL (windows.h)
    Sleep(100);
	moveItem(from, to);
    Sleep(100); 
    SendMessage(hWnd, WM_SYSKEYUP, VK_CONTROL, 1); // Let go of CTRL  (windows.h)
    Sleep(100);
}

void events::castSpell(){ 
    SendMessage(hWnd, WM_SYSKEYDOWN, VK_F10, 0); // Press down F2 key (windows.h)
    Sleep(rand()%180+100); 
    SendMessage(hWnd, WM_SYSKEYUP, VK_F10, 0); // Let go of F2 key (windows.h)
    Sleep(rand()%180+100); 
}



bool events::keyIsPressed ( unsigned char k ){
    USHORT status = GetAsyncKeyState ( k );
	// Bitwise AND comparison between 100000~ and 1111
    return (( ( status & 0x8000 ) >> 15 ) == 1) || (( status & 1 ) == 1);
}

void events::setReadUserInput(bool readUserInput){
    this->readUserInput = readUserInput; // Set member variable to param
}
void events::waitForUserInput(){
    while(readUserInput){
        if(keyIsPressed(VK_PAUSE)) 
            pauseBot=!pauseBot;
        Sleep(10);
    }
}

void events::isPaused(){
	std::chrono::milliseconds dura( 2000 );
    while(pauseBot){
		std::this_thread::sleep_for( dura );
        //Sleep(100);
    }
}
