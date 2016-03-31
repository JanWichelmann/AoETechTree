#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes
#include "BaseUnitData.h"


/* DEFINITIONS */

#pragma pack(push, 1)
// Contains the civilization data and units.
class CivData : public GameType
{
public: // Member variables (public for simplicity reasons...maybe put wrapper functions around them later?)
	int _VTable;
	char _name[20];
	short _unitCount;
	short _unknown1;
	BaseUnitData **_units;
	short _resourceCount;
	char gap_22[2];
	float *_resources;
	char _iconSet;
	char _isX1Civ;
	short _civBonusId;
	short _teamBonusId;
	short _unknown4;

public:

};
#pragma pack(pop)

