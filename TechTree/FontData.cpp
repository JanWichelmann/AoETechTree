/* INCLUDES */

// Class header
#include "FontData.h"

/* FUNCTIONS */

HFONT FontData::GetFontHandle()
{
	// Return handle
	return _fontHandle;
}

int FontData::GetCharHeightWithRowSpace()
{
	// Return height
	return _charHeightWithRowSpace;
}

int FontData::GetAverageCharWidth()
{
	// Return width
	return _averageCharWidth;
}