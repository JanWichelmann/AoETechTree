#pragma once

/* INCLUDES */

// Base class header
#include "Control.h"

// Other includes

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents a text box.
class TextBoxControl : public Control
{
protected: // Member variables
	HWND _textBoxHWnd;
	char _unknown100a[52];
	HFONT _fontHandle;
	char _unknown100b[32];
	int _unknownBevelColorRelated;
	char _bevelColors[6];
	char _unknown100c[22];

public:
};
#pragma pack(pop)