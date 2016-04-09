#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents an unknown control related class.
// Research type name: AnotherWindowRelatedStruct.
class AnotherControlRelatedClass : public GameType
{
protected: // Member variables
	DWORD _unknown1[27];
	DWORD _flag;
	DWORD _unknown2[8];
	DWORD _width;
	DWORD _height;
	DWORD _positionX;
	DWORD _positionY;

public:
};
#pragma pack(pop)
