#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes

/* DEFINITIONS */

#pragma pack(push, 1)
// Contains the data of a specific game font.
class FontData : public GameType
{
protected: // Member variables
	HFONT _fontHandle;
	int _averageCharWidth;
	int _charHeightWithRowSpace;

public:
	// Returns the GDI font handle.
	HFONT GetFontHandle();

	// Returns the char height including row space.
	int GetCharHeightWithRowSpace();

	// Returns the average char width.
	int GetAverageCharWidth();
};
#pragma pack(pop)
