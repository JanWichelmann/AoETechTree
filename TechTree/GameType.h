#pragma once

/* INCLUDES */

// Windows main header
#define NOMINMAX
#include <Windows.h>

// Code cave functions
#include "functions.h"

/* MACROS */

// Creates a static wrapper function for the given virtual function table method METHOD.
// It has to be installed in the __Install function of the corresponding class using the second macro.
#define CONCATSUB(x, y) x ## _ ## y
#define CONCAT(x, y) CONCATSUB(x, y)
#define STATIC_WRAPPER(METHOD, RETURNTYPE, ...)	typedef RETURNTYPE(__thiscall CLASS::*CONCAT(FuncPtrType, CONCAT(CLASS, METHOD)))(##__VA_ARGS__);\
							typedef RETURNTYPE(__thiscall *CONCAT(FreeFuncPtrType, CONCAT(CLASS, METHOD)))(CLASS *, ##__VA_ARGS__);\
							CONCAT(FuncPtrType, CONCAT(CLASS, METHOD)) CONCAT(FuncPtr, CONCAT(CLASS, METHOD)) = &##CLASS##::##METHOD;\
							CONCAT(FreeFuncPtrType, CONCAT(CLASS, METHOD)) CONCAT(CLASS, METHOD);\
							__declspec(naked) void CONCAT(StaticWrapper, CONCAT(CLASS, METHOD))()\
							{\
								__asm jmp CONCAT(FuncPtr, CONCAT(CLASS, METHOD))\
							}
#define INSTALL_WRAPPER_VIRTUAL(METHOD, ADDRESS) CONCAT(CLASS, METHOD) = (CONCAT(FreeFuncPtrType, CONCAT(CLASS, METHOD)))ReadVTableEntry(ADDRESS);\
							CreateVTableEntry(ADDRESS, CONCAT(StaticWrapper, CONCAT(CLASS, METHOD)));
#define INSTALL_WRAPPER_DIRECT(METHOD, ADDRESS) CONCAT(CLASS, METHOD) = nullptr;\
                            CreateCodecave(ADDRESS, CONCAT(StaticWrapper, CONCAT(CLASS, METHOD)), 0);

/* DEFINITIONS */

#pragma pack(push, 1)
// This is a base class for all game executable types overridden in this program; derived classes work as an interface for a specific game type.
// They access the corresponding virtual function tables to maintain compability with the original game types while also adding (or replacing) functionality.
class GameType
{
protected: // Member variables
	// None

public:
	// Installs the class in game code.
	// This includes replacing virtual function table entries and function calls, creating code caves etc.
	static void __Install()
	{
		// Nothing to do here
	}
};
#pragma pack(pop)
