#pragma once
/*
--- AOE AGE PATCH :: INJECTION CODE ---
*/

/* INCLUDES */

// Windows definitions
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

// C standard I/O functions
#include <cstdio>

/* MAKROS */

// Maximum string length.
#define MAX_STRING_LENGTH MAX_PATH

/* FUNKTIONEN */

// Loads the given DLL function into the given process and runs it in its context.
// Parameters:
// -> process: The process to inject the DLL into.
// -> dllPath: The path to the DLL being injected.
// -> dllFunc: The DLL initialization function to be run after successful injection.
void InjectDLL(HANDLE process, const char* dllPath, const char* dllFunc)
{
	// Path to DLL
	DWORD addrInjectDLLPath = 0;
	char injectDLLPath[MAX_STRING_LENGTH + 1] = { 0 };
	_snprintf_s(injectDLLPath, MAX_STRING_LENGTH + 1, MAX_STRING_LENGTH, "%s", dllPath);

	// DLL initialization function
	DWORD addrInjectDLLFunc = 0;
	char injectDLLFunc[MAX_STRING_LENGTH + 1] = { 0 };
	_snprintf_s(injectDLLFunc, MAX_STRING_LENGTH + 1, MAX_STRING_LENGTH, "%s", dllFunc);

	// Error message box title
	DWORD addrInjectErrorTitle = 0;
	char injectErrorTitle[MAX_STRING_LENGTH + 1] = { 0 };
	_snprintf_s(injectErrorTitle, MAX_STRING_LENGTH + 1, MAX_STRING_LENGTH, "Error");

	// Error message: DLL loading failed
	DWORD addrInjectError1 = 0;
	char injectError1[MAX_STRING_LENGTH + 1] = { 0 };
	_snprintf_s(injectError1, MAX_STRING_LENGTH + 1, MAX_STRING_LENGTH, "Couldn't load the inject DLL '%s'.\nThe program will exit now.", injectDLLPath);

	// Error message: Initialization function call failed
	DWORD addrInjectError2 = 0;
	char injectError2[MAX_STRING_LENGTH + 1] = { 0 };
	_snprintf_s(injectError2, MAX_STRING_LENGTH + 1, MAX_STRING_LENGTH, "Couldn't load the inject DLL init function '%s'.\nThe program will exit now.", injectDLLFunc);

	// Load kernel32.dll
	HMODULE kernel32 = LoadLibraryA("kernel32.dll");

	// Get addresses of some kernel32 functions
	FARPROC procLoadLibraryA = GetProcAddress(kernel32, "LoadLibraryA");
	FARPROC procGetProcAddress = GetProcAddress(kernel32, "GetProcAddress");
	FARPROC procExitProcess = GetProcAddress(kernel32, "ExitProcess");
	FARPROC procExitThread = GetProcAddress(kernel32, "ExitThread");

	// Load user32.dll
	// It's already loaded by Age of Empires, so we don't have to load it there
	HMODULE user32 = LoadLibraryA("user32.dll");

	// Get address of MessageBox function (for error messages)
	FARPROC procMessageBoxA = GetProcAddress(user32, "MessageBoxA");

	// Execution offset in reserved memory
	DWORD addrExecBegin = 0;

	// Reserve memory for patch and allocate it in the target process
	LPBYTE mem = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 1024);
	LPVOID memProcAddr = VirtualAllocEx(process, 0, 1024, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	DWORD memProcAddrVal = PtrToUlong(memProcAddr);

	/*** DATA ***/

	// Pointer for writing in our reserved memory
	DWORD memPos = 0;

	// Auxiliary variable
	DWORD tempSize = 0;

	// Write DLL name
	addrInjectDLLPath = memProcAddrVal + memPos;
	tempSize = (DWORD)strlen(injectDLLPath) + 1; // Null-Byte am Ende nicht vergessen
	memcpy(mem + memPos, injectDLLPath, tempSize);
	memPos += tempSize;

	// Write initialization function name
	addrInjectDLLFunc = memProcAddrVal + memPos;
	tempSize = (DWORD)strlen(injectDLLFunc) + 1;
	memcpy(mem + memPos, injectDLLFunc, tempSize);
	memPos += tempSize;

	// Write error message title
	addrInjectErrorTitle = memProcAddrVal + memPos;
	tempSize = (DWORD)strlen(injectErrorTitle) + 1;
	memcpy(mem + memPos, injectErrorTitle, tempSize);
	memPos += tempSize;

	// Write error message 1
	addrInjectError1 = memProcAddrVal + memPos;
	tempSize = (DWORD)strlen(injectError1) + 1;
	memcpy(mem + memPos, injectError1, tempSize);
	memPos += tempSize;

	// Write error message 2
	addrInjectError2 = memProcAddrVal + memPos;
	tempSize = (DWORD)strlen(injectError2) + 1;
	memcpy(mem + memPos, injectError2, tempSize);
	memPos += tempSize;

	// Save code segment start
	addrExecBegin = memProcAddrVal + memPos;

	/*** DLL LOAD CODE ***/
	// The following commands are assembled by hand.
	// They are separated from each other to keep the code clear.

	// push addr
	// -> Push DLL name for LoadLibraryA onto the stack
	mem[memPos++] = 0x68;
	memcpy(mem + memPos, &addrInjectDLLPath, 4);
	memPos += 4;

	// mov eax, addr
	// -> Put address of LoadLibraryA into EAX
	mem[memPos++] = 0xB8;
	memcpy(mem + memPos, &procLoadLibraryA, 4);
	memPos += 4;

	// call eax
	// -> Call LoadLibraryA
	mem[memPos++] = 0xFF;
	mem[memPos++] = 0xD0;

	// Error checking => When errors occur EAX will be 0
	{
		// cmp eax, 0
		// -> Are there errors?
		mem[memPos++] = 0x83;
		mem[memPos++] = 0xF8;
		mem[memPos++] = 0x00;

		// jnz eip+0x1E
		// -> If not, skip error code (30 bytes)
		mem[memPos++] = 0x75;
		mem[memPos++] = 0x1E;

		// push 0x10
		// -> Push message box icon ID (MB_ICONHAND) onto the stack
		mem[memPos++] = 0x6A;
		mem[memPos++] = 0x10;

		// push addr
		// -> Push address of error message title onto the stack
		mem[memPos++] = 0x68;
		memcpy(mem + memPos, &addrInjectErrorTitle, 4);
		memPos += 4;

		// push addr
		// -> Push address of error message onto the stack
		mem[memPos++] = 0x68;
		memcpy(mem + memPos, &addrInjectError1, 4);
		memPos += 4;

		// push 0
		// -> Push message box window handle onto the stack
		mem[memPos++] = 0x6A;
		mem[memPos++] = 0x00;

		// mov eax, addr
		// -> Put address of MessageBoxA into EAX
		mem[memPos++] = 0xB8;
		memcpy(mem + memPos, &procMessageBoxA, 4);
		memPos += 4;

		// call eax
		// -> Call MessageBoxA and show error message
		mem[memPos++] = 0xFF;
		mem[memPos++] = 0xD0;

		// push 0
		// -> Push error code for ExitProcess onto the stack
		mem[memPos++] = 0x6A;
		mem[memPos++] = 0x00;

		// mov eax, addr
		// -> Put address of ExitProcess into EAX
		mem[memPos++] = 0xB8;
		memcpy(mem + memPos, &procExitProcess, 4);
		memPos += 4;

		// call eax
		// -> Call ExitProcess, end of execution
		mem[memPos++] = 0xFF;
		mem[memPos++] = 0xD0;
	}

	// push addr
	// -> Push address of initialization function for GetProcAddress onto the stack
	mem[memPos++] = 0x68;
	memcpy(mem + memPos, &addrInjectDLLFunc, 4);
	memPos += 4;

	// push eax
	// -> Push DLL handle onto the stack (still in EAX)
	mem[memPos++] = 0x50;

	// mov eax, addr
	// -> Put address of GetProcAddress into EAX
	mem[memPos++] = 0xB8;
	memcpy(mem + memPos, &procGetProcAddress, 4);
	memPos += 4;

	// call eax
	// -> Call GetProcAddress
	mem[memPos++] = 0xFF;
	mem[memPos++] = 0xD0;

	// Error checking => When errors occur EAX will be 0
	{
		// cmp eax, 0
		// -> Are there errors?
		mem[memPos++] = 0x83;
		mem[memPos++] = 0xF8;
		mem[memPos++] = 0x00;

		// jnz eip+0x1E
		// -> If not, skip error code (28 bytes)
		mem[memPos++] = 0x75;
		mem[memPos++] = 0x1C;

		// push 0x10
		// -> Push message box icon ID (MB_ICONHAND) onto the stack
		mem[memPos++] = 0x6A;
		mem[memPos++] = 0x10;

		// push addr
		// -> Push address of error message title onto the stack
		mem[memPos++] = 0x68;
		memcpy(mem + memPos, &addrInjectErrorTitle, 4);
		memPos += 4;

		// push addr
		// -> Push address of error message onto the stack
		mem[memPos++] = 0x68;
		memcpy(mem + memPos, &addrInjectError2, 4);
		memPos += 4;

		// push 0
		// -> Push message box window handle onto the stack
		mem[memPos++] = 0x6A;
		mem[memPos++] = 0x00;

		// mov eax, addr
		// -> Put address of MessageBoxA into EAX
		mem[memPos++] = 0xB8;
		memcpy(mem + memPos, &procMessageBoxA, 4);
		memPos += 4;

		// call eax
		// -> Call MessageBoxA and show error message
		mem[memPos++] = 0xFF;
		mem[memPos++] = 0xD0;

		// push 0
		// -> Push error code for ExitProcess onto the stack
		mem[memPos++] = 0x6A;
		mem[memPos++] = 0x00;

		// mov eax, addr
		// -> Put address of ExitProcess into EAX
		mem[memPos++] = 0xB8;
		memcpy(mem + memPos, &procExitProcess, 4);
		memPos += 4;
	}

	// call eax
	// Depending on value of EAX (see error checking):
	// -> Call ExitProcess, end of execution
	// -> Call initialization function (address should be in EAX if no errors occured)
	mem[memPos++] = 0xFF;
	mem[memPos++] = 0xD0;

	/*** END OF DLL LOAD CODE ***/
	// The DLL stays loaded, the loading thread is terminated.

	// push 0
	// -> Push error code for ExitThread onto the stack
	mem[memPos++] = 0x6A;
	mem[memPos++] = 0x00;

	// mov eax, addr
	// -> Put address of ExitThread into EAX
	mem[memPos++] = 0xB8;
	memcpy(mem + memPos, &procExitThread, 4);
	memPos += 4;

	// call eax
	// -> Call ExitThread, end of execution
	mem[memPos++] = 0xFF;
	mem[memPos++] = 0xD0;

	/*** INJECT THE LOAD CODE ***/

	// Change page protection to inject our patch
	DWORD pageProtectOld = 0;
	VirtualProtectEx(process, memProcAddr, memPos, PAGE_EXECUTE_READWRITE, &pageProtectOld);

	// Write patch into process memory
	DWORD writtenByteCount = 0;
	WriteProcessMemory(process, memProcAddr, mem, memPos, &writtenByteCount);

	// Restore page protection
	VirtualProtectEx(process, memProcAddr, memPos, pageProtectOld, &pageProtectOld);

	// Flush the CPU's instruction cache to make sure it'll really execute our patch
	FlushInstructionCache(process, memProcAddr, memPos);

	// Free our local patch memory
	HeapFree(GetProcessHeap(), 0, mem);

	// Run DLL loading thread
	// The start address is the offset where our load code starts (addrExecBegin)
	HANDLE loaderThread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)ULongToPtr(addrExecBegin), 0, 0, NULL);

	// Wait for the loading thread to exit
	WaitForSingleObject(loaderThread, INFINITE);

	// Free the memory allocated in the process
	VirtualFreeEx(process, memProcAddr, 0, MEM_RELEASE);
}
