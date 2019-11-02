#pragma once

/* INCLUDES */

// Windows main header
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

// Code cave functions
#include "functions.h"

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
