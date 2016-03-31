#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes


/* DEFINITIONS */

#pragma pack(push, 1)
// Contains the researches.
class ResearchDataItem : public GameType
{
public: // Member variables (public for simplicity reasons...maybe put wrapper functions around them later?)
	char *_name;
	short _requiredTechIds[6];
	short _requiredTechCount;
	short _civ;
	short _fullTechMode;
	short _resourceCostTypes[3];
	short _resourceCostAmounts[3];
	char _resourceCostEnableds[3];
	char gap1;
	short _researchTime;
	short _techageID;
	short _type;
	short _iconID;
	char _buttonId;
	char gap2;
	short _researchLocation;
	short _languageDLLName1;
	short _languageDLLDescription;
	short gap3;
	int _languageDLLHelp;
	int _languageDLLName2;
	int _unknown1;

public:

};
#pragma pack(pop)

