#pragma once

/* INCLUDES */

// Base class headers
#include "GameType.h"

// Other includes

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents a format for a specific text.
class TextFormatData : public GameType
{
protected: // Member variables
	int _textIndex;
	int _formatValue;
	TextFormatData *_nextFormatData;

public:
};
#pragma pack(pop)
