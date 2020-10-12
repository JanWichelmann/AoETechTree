#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"
#include "VTableType.h"

#include "ColorTable.h"

/* DEFINITIONS */

class PlayerVTable;

class Player : public GameType
{
public:
	PlayerVTable *_VTable;

private:
	char _padding[345];
	char _civId;
	char _padding2[2];
	ColorTable *_colorTable;
	char _padding3[6102];
	char _diplomaticStances[9];

public:
	int GetCivId() const { return _civId; }
	ColorTable *GetColorTable() const { return _colorTable; }
	char GetDiplomaticStance(int other) const { return _diplomaticStances[other]; }
};

class PlayerVTable : public VTableType
{
};
