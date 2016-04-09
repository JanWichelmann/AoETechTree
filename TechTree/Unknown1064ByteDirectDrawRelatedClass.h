#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an unknown class type with a length of 1064 bytes. It is related to the DirectDrawBufferData class and widely used.
class Unknown1064ByteDirectDrawRelatedClass : public GameType
{
protected: // Member variables
	BYTE _gap0[4];
	int _maybeWidthOrBytesPerLine;
	int _heightOrSomethingMaybeInvertedYAxisRelated;
	DWORD _gap1[263];

public:
};
#pragma pack(pop)
