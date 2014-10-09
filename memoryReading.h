#pragma once
#include <windows.h>
#include <vector>


class memoryReading
{
public:
	/**
	 * @brief retrieves necessary information for memory reading
	 * @details retrieves information such as base address, process ID etc
	 */
	memoryReading();

	/**
	 * @brief closes Phandle
	 * @details closes the Phandle to avoid issues
	 */
	~memoryReading(void);

	/**
	 * @brief memory reading function
	 * @details reads memory with base address + offsets
	 * 
	 * @param v vector with all offsets
	 * @return value read at specified memory address
	 */
	int readMemory( const std::vector<DWORD> v  );

private:
	/**
	 * @brief gets base address
	 * @details retrieves the base address from Tibianic.dll
	 * 
	 * @param tibianicPID Process ID of Tibia client
	 * @return returns the base address
	 */
	DWORD getStartAddress(DWORD TibianicPID);

	BOOL SetPrivilege(
		HANDLE hToken,          // access token handle
		LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
		BOOL bEnablePrivilege   // to enable or disable privilege
		);

	DWORD Address;		 ///< base address of Tibianic.dll
	HANDLE phandle; 	 ///< handle to open the process
	HWND hWnd;			 ///< handle for Tibiaclient
	DWORD TibianicPID; 	 ///< this will store our Process ID, used to read/write into the memory
	HANDLE hProcessSnap; ///< handle to take snapshot of all modules
	
};

