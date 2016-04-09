#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes
#include "ResearchDataItem.h"

/* DEFINITIONS */

// Class prototype to avoid include loops
class GameDataHandler;

#pragma pack(push, 1)
// Contains the researches.
class ResearchData : public GameType
{
public: // Member variables (public for simplicity reasons...maybe put wrapper functions around them later?)
	ResearchDataItem *_researches;
	short _researchCount;
	short gap;
	GameDataHandler *_gameDataHandler;

public:
};
#pragma pack(pop)
