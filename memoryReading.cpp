#include "stdafx.h"
#include "memoryReading.h"
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <TlHelp32.h>
#include <iostream>
#include <cstring>
#include <tchar.h>
#include "AccesDeniedError.h"

memoryReading::memoryReading(void){
	HWND hWnd = FindWindow( NULL , _T("Tibianic Client") );

	//Get the process id and place it in pid
	GetWindowThreadProcessId(hWnd, &TibianicPID); 

	// Handle for the snapshot
	hProcessSnap = NULL;

	// TH32CS_SNAPMODULE Includes all modules of the process specified in th32ProcessID in the snapshot. 
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, TibianicPID);

	// Get base address from Tibianic.dll
	Address = getStartAddress(TibianicPID);

	DWORD cbNeeded;		// Necessary to get a list of process idenifiers
	DWORD aProcesses[1024]; // Necessary to get a list of process idenifiers

    // Get the list of process identifiers.
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		throw (std::exception("Memory reading failed")); //std::cerr << "Memory reading failed. ";

	/* Opening process */
    phandle = OpenProcess(PROCESS_VM_READ,0, TibianicPID); // Get permission to read
    if(!phandle){ // Once again, if it fails, tell us
		throw AccesDeniedError(GetLastError());
	}
}


memoryReading::~memoryReading(void){
	CloseHandle(phandle);
}

DWORD memoryReading::getStartAddress(DWORD TibianicPID)
{
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return 0;

	MODULEENTRY32 the;
	the.dwSize = sizeof(MODULEENTRY32);

	// name of dll file to be compared with
	const char *dllName = "Tibianic.dll";

	// Initiate bret with the first module
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


 
int memoryReading::readMemory( const std::vector<DWORD> v )
{
	DWORD tmpAddress;
	tmpAddress = Address; // Base address of Tibianic.dll

	/* This part is incomplete HUD implementation */
	HDC hdc = GetDC(hWnd);
	RECT rect;
	GetClientRect(hWnd, &rect);
	char * text = "WOOP WOOP WOOP WOOP WOOP WOOP WOOP WOOP";
	DrawTextA(hdc, text, strlen(text), &rect, DT_CENTER | DT_VCENTER);
	ReleaseDC(hWnd, hdc);
	/* End HUD implementation here */



	/* Reading Memory 
	 * Reads memory from tmpAddress+v[i] and put value into tmpAddress then iterate this on all offsets
	 * then read the final value from tmpAddress and save it in tmpAddress.
	*/
	for (size_t i = 0; i < v.size(); i++){
		ReadProcessMemory(phandle,(void*)(tmpAddress+v[i]),&tmpAddress,sizeof(tmpAddress),0);
	}
	ReadProcessMemory(phandle,(void*)(tmpAddress),&tmpAddress,sizeof(tmpAddress),0);
	return (int)tmpAddress;
}
