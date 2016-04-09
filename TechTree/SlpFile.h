#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

// Other includes
#include "SlpFrameHeader.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an SLP file.
class SlpFile : public GameType
{
protected: // Member variables
	char Version[4];
	int FrameCount;
	char Copyright[24];
	SlpFrameHeader FirstFrameHeader;

public:
};
#pragma pack(pop)