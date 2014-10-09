// test.cpp : Defines the entry point for the console application.
//
 
#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <TlHelp32.h>
#include <iostream>
#include <cstring>
#include <tchar.h>
#include <vector>
// To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS
// and compile with -DPSAPI_VERSION=1
 


DWORD get_start_address(DWORD TibianicPID)
{
	// Handle for the snapshot
	HANDLE hProcessSnap = NULL;

	// TH32CS_SNAPMODULE Includes all modules of the process specified in th32ProcessID in the snapshot. 
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, TibianicPID);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return 0;

	MODULEENTRY32 the;
	the.dwSize = sizeof(MODULEENTRY32);
	const char *dllName = "Tibianic.dll";

	BOOL bret = Module32First( hProcessSnap, &the); // Initiate bret with module
	while(bret)
	{
		if(wcscmp(the.szModule, _T("Tibianic.dll"))==0) // Compare with current value
		    return (DWORD)the.modBaseAddr;
				
		// Fetch next dll loaded address
		bret = Module32Next(hProcessSnap, &the);
	}
	return 0;
}


 
int main( void )
{
	DWORD pAddress3 = 0x00400000; // This will store our value we read.
	DWORD pAddressHpBase;
	DWORD pBattleList;
	
	//vector<DWORD> v = {};
	DWORD offset5 = 0x378;
	DWORD offset4 = 0x218;
	DWORD offset3 = 0x10C;
	DWORD offset2 = 0x1C0;
	DWORD offset1 = 0x78;
	DWORD offset0 = 0xF3090;
	//TCHAR Modname[MAX_PATH];
 
	HWND hWnd = FindWindow( NULL , _T("Tibianic Client") );
	DWORD TibianicPID; //This will store our Process ID, used to read/write into the memory
	GetWindowThreadProcessId(hWnd, &TibianicPID); //Get the process id and place it in pid
 
    DWORD aProcesses[1024];
    DWORD cbNeeded;
 
    // Get the list of process identifiers.
    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return 1;
 

 
   
	pAddress3 = get_start_address(TibianicPID);
	pAddressHpBase = pAddress3;
	pBattleList = pAddress3;
 
        /* Reading Memory & Opening process */
        HANDLE phandle = OpenProcess(PROCESS_VM_READ,0, TibianicPID); // Get permission to read
    if(!phandle){ // Once again, if it fails, tell us
            std::cout <<"Error message: " << GetLastError() << " Dvs Access denied" << std::endl;
            std::cin.get();
            return 0;
    }
    //std::cout << "Base address is: " << pAddress3 << std::endl;
    ReadProcessMemory(phandle,(void*)(pAddressHpBase+0xF40F0),&pAddressHpBase,sizeof(pAddressHpBase),0);
	pAddressHpBase += 4;
    ReadProcessMemory(phandle,(void*)(pAddressHpBase),&pAddressHpBase,sizeof(pAddressHpBase),0);
    std::cout << "Your HP is: " << pAddressHpBase << std::endl;
 
	//std::cout << "Base address is: " << pAddress3 << std::endl;
    ReadProcessMemory(phandle,(void*)(pBattleList+0x319D68),&pBattleList,sizeof(pBattleList),0);
	pAddressHpBase += 0x12A;
    ReadProcessMemory(phandle,(void*)(pBattleList),&pBattleList,sizeof(pBattleList),0);
    std::cout << "Battle list: " << (char)pBattleList << std::endl;
 

	SIZE_T size;
	ReadProcessMemory(phandle,(void*)(pAddress3+0xF40F0),&pAddress3,sizeof(pAddress3),&size);
	ReadProcessMemory(phandle,(void*)(pAddress3),&pAddress3,sizeof(pAddress3),&size);
    std::cout << "You mana is: " << pAddress3 << std::endl;

	std::cin.get();
    return 0;
}