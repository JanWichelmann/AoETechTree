/*
--- AOE TECH TREE REPLACEMENT :: MAIN FILE ---
*/


/* INCLUDES */

// Codecave functions
#include "functions.h"

// Installed classes
#include "TechTreeWindow.h"
#include "TechTreeData.h"


/* GLOBAL OPERATOR OVERRIDES */

// Override new operator with game new operator.
void *operator new(unsigned int size)
{
	// Call game new
	return ((void *(__cdecl *)(unsigned int))0x006137B0)(size);
}

// Override delete operator with game delete operator.
void operator delete(void *ptr)
{
	// Call game delete
	((void(__cdecl *)(void *))0x006137BE)(ptr);
}


/* DLL FUNCTION */

// DLL entry point.
int WINAPI DllMain(HMODULE hModule, DWORD ulReason, LPVOID)
{
	// Disable DLL thread messages
	if(ulReason == DLL_PROCESS_ATTACH)
		DisableThreadLibraryCalls(hModule);

	// Always load
	return TRUE;
}

// Initialization function.
extern "C" __declspec(dllexport) void Init()
{
	// Install classes
	TechTreeWindow::__Install();
	TechTreeData::__Install();
}

