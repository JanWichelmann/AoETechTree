#pragma once

/* INCLUDES */

// Base class header
#include "ButtonControl.h"

// Other includes

/* DEFINITIONS */

// Class prototype to avoid include loops
class ComboBoxControl;

#pragma pack(push, 1)
// Represents a drop down button (used for combo boxes).
class DropDownButtonControl : public ButtonControl
{
protected: // Member variables
	ComboBoxControl *_parentComboBox;

public:

};
#pragma pack(pop)