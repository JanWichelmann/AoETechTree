#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an unknown class, probably palette related.
class ColorTable : public GameType
{
protected: // Member variables
	DWORD _VTable;

public:
	int ResourceId;
	int Type;
	char* Table;
	int ColorTransformBase;
	int UnitOutlineColor;
	int SelectionColor1;
	int SelectionColor2;
	int MinimapColor1;
	int MinimapColor2;
	int MinimapColor3;
	int TextColor1;
	int TextColor2;
	char TextColorR;
	char TextColorG;
	char TextColorB;
private:
	char reserved_;
};
#pragma pack(pop)
