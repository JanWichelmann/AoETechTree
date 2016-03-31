/*
--- AOE TECH TREE REPLACEMENT :: LOADER ---
*/

/* INCLUDES */

// Windows definitions
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// C standard I/O functions
#include <cstdio>

// __argc, __argv-Variablen for command line parsing
#include <cstdlib>

// C++ string functions
#include <string>

// Injecton functions
#include "injection.h"


/* FUNCTIONS */

// Application entry point.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow)
{
	// The current folder is our working directory
	// The string has a length of MAX_STRING_LENGTH for simply copying later
	char workdir[MAX_STRING_LENGTH + 1] = { 0 };
	GetCurrentDirectory(MAX_STRING_LENGTH, workdir);

	// Path to our executable
	char exepath[MAX_STRING_LENGTH + 1] = { 0 };

	// Parse executable parameters
	std::string cmdLine("age2_x1.exe nostartup");
	if(__argc > 1)
		cmdLine = std::string("");
	for(int i = 1; i < __argc; ++i)
	{
		// Concat parameter string
		cmdLine.append(__argv[i]).append(" ");
	}

	// Combine path and parameters
	// nostartup: Disable startup videos
	_snprintf_s(exepath, MAX_STRING_LENGTH, MAX_STRING_LENGTH, "%s\\%s", workdir, cmdLine.c_str());

	// DLL path
	char dllpath[MAX_STRING_LENGTH + 1] = { 0 };
	_snprintf_s(dllpath, MAX_STRING_LENGTH, MAX_STRING_LENGTH, "TechTree.dll");
	
	// Variables for process startup
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi = { 0 };

	// Pass size of STARTUPINFO structure
	si.cb = sizeof(STARTUPINFO);

	// Run EXE, but suspend immediately
	int res = CreateProcess(NULL, exepath, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, workdir, &si, &pi);
	if(res == 0)
	{
		// Argh
		MessageBoxA(0, "Couldn't run specified executable!", "Error", MB_ICONERROR);

		// Cancel
		return -1;
	}

	// Perform DLL injection
	InjectDLL(pi.hProcess, dllpath, "Init");
	
	// Resume EXE
	ResumeThread(pi.hThread);

	// Exit loader
	return 0;
}


