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
	// Debug code for buffer overflow detection
	// Puts two large 256 marker byte chunks before and after the allocated memory, which are then checked on deallocation.
	// This will likely crash the game when destructing some controls, because the game destructor doesn't call the modified delete[] operator.
	// But as long as one doesn't close the tech tree window, these lines shouldn't cause any further problems.
	/*void *mem = ((void *(__cdecl *)(unsigned int))0x006137B0)(4 + 256 + size + 256 + 1);
	reinterpret_cast<int *>(mem)[0] = size;
	for(int i = 0; i < 256; ++i)
		reinterpret_cast<unsigned char *>(mem)[4 + i] = 0xF0;
	for(int i = 0; i < 256; ++i)
		reinterpret_cast<unsigned char *>(mem)[4 + 256 + size + i] = 0xF1;
	reinterpret_cast<unsigned char *>(mem)[4 + 256 + size + 256] = 0x00; // Deleted flag
	return (void*)((int)mem + 4 + 256);*/

	// Call game new
	return ((void *(__cdecl *)(unsigned int))0x006137B0)(size);
}

// Override delete operator with game delete operator.
void operator delete(void *ptr)
{
	// Debug code for buffer overflow detection
	/*void *mem = (void *)((int)ptr - 4 - 256);
	int size = ((int *)mem)[0];
	for(int i = 0; i < 256; ++i)
		if(reinterpret_cast<unsigned char *>(mem)[4 + i] != 0xF0)
			__asm int 3;
	for(int i = 0; i < 256; ++i)
		if(reinterpret_cast<unsigned char *>(mem)[4 + 256 + size + i] != 0xF1)
			__asm int 3;
	if(reinterpret_cast<unsigned char *>(mem)[4 + 256 + size + 256] != 0x00)
		__asm int 3;
	reinterpret_cast<unsigned char *>(mem)[4 + 256 + size + 256] = 0x01;
	((void(__cdecl *)(void *))0x006137BE)(mem);*/

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