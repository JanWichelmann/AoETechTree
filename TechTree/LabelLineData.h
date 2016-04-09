#pragma once

/* INCLUDES */

// Base class headers
#include "GameType.h"

// Other includes
#include "TextFormatData.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents a container for a label's line data.
class LabelLineData : public GameType
{
protected: // Member variables
	char *_lineText;
	char *_lineText2;
	int _id;
	TextFormatData *_lineFormatData;
	char _byte10;
	char _gap11[19];
	char _byte24;
	char _gap_25[3];
	int _dword28;
	LabelLineData *_nextLineData;

public:
};
#pragma pack(pop)
