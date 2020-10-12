#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

/* DEFINITIONS */

// Class prototype to avoid include loops
class DirectDrawArea;

#pragma pack(push, 1)
// Represents an DirectDraw buffer handler list element.
class DirectDrawAreaNode : public GameType
{
protected: // Member variables
	DirectDrawArea *_data;
	DirectDrawAreaNode *_previousElement;
	DirectDrawAreaNode *_nextElement;

public:
};
#pragma pack(pop)
