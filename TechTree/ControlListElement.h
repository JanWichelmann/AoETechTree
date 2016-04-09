#pragma once

/* INCLUDES */

// Base class header
#include "GameType.h"

/* DEFINITIONS */

// Class prototype to avoid include loops
class Control;

#pragma pack(push, 1)
// Represents an element of a control list.
// Research type name: DoubleLinkedListElement.
class ControlListElement : public GameType
{
public: // Member variables
	Control *AssociatedControl;
	ControlListElement *PreviousElement;
	ControlListElement *NextElement;

public:
};
#pragma pack(pop)
