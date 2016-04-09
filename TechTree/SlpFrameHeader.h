#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an SLP file frame header.
class SlpFrameHeader : public GameType
{
protected: // Member variables
	int FrameCommandsOffset;
	int FrameOutlineOffset;
	int PaletteOffset;
	int Properties;
	int Width;
	int Height;
	int AnchorX;
	int AnchorY;

public:
};
#pragma pack(pop)