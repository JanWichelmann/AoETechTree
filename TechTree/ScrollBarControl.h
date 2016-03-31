#pragma once

/* INCLUDES */

// Base class header
#include "Control.h"

// Other includes
#include "SlpFileElement.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents a scroll bar.
class ScrollBarControl : public Control
{
protected: // Member variables
	Control *_scrolledControl;
	char _unknown100a[16];
	SlpFileElement *_designSlp;
	int _designSlpUnknownValue;
	int _designSlpScrollUpFrameIndex;
	int _designSlpScrollDownFrameIndex;
	int _designSlpScrollBlockFrameIndex;
	int _maybeUpButtonWidth;
	int _maybeDownButtonWidth;
	char _unknown100b1[148];
	int _unknownBevelColorRelated;
	char _bevelColors[6];
	short _unknown100b2;

public:

};
#pragma pack(pop)