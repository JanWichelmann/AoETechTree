#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

/* DEFINITIONS */

// Class prototype to avoid include loops
class DirectDrawBufferData;

#pragma pack(push, 1)
// Represents an DirectDraw buffer handler list element.
class DirectDrawBufferDataListElement : public GameType
{
protected: // Member variables
	DirectDrawBufferData *_data;
	DirectDrawBufferDataListElement *_previousElement;
	DirectDrawBufferDataListElement *_nextElement;

public:
};
#pragma pack(pop)
