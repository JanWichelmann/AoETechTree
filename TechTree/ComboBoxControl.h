#pragma once

/* INCLUDES */

// Base class header
#include "Control.h"

// Other includes
#include "LabelControl.h"
#include "DropDownButtonControl.h"
#include "ListBoxControl.h"
#include "ScrollBarControl.h"

/* DEFINITIONS */

#pragma pack(push, 1)
// Represents a combo box.
class ComboBoxControl : public Control
{
protected: // Member variables
	LabelControl *_valueLabel;
	DropDownButtonControl *_dropDownButton;
	ListBoxControl *_dropDownList;
	ScrollBarControl *_dropDownListScrollBar;
	int _childUnknown5;
	short _unknownStringPointerIndex;
	short _childUnknown6b;
	int _valueLabelWidth;
	int _valueLabelHeight;
	int _dropDownButtonWidth;
	int _dropDownButtonHeight;
	int _dropDownListWidth;
	int _dropDownListHeight;
	int _childUnknown13;
	int _dropDownListScrollBarWidth;
	int _childUnknown15;
	int _childUnknown16;
	int _childUnknown17;
	int _childUnknown18;
	int _childUnknown19;
	int _childUnknown20;
	int _childUnknown21;
	int _childUnknown22;
	int _unknownBevelColorRelated;
	char _bevelColors[6];
	short _childUnknown25;
	int _styleText1Color1_BGR;
	int _styleText1Color2_BGR;
	int _childUnknown28;
	int _childUnknown29;
	int _childUnknown30;
	int _childUnknown31;

public:
	// Sets the sorting mode.
	// Parameters:
	// -> sort: The sorting mode (0: no sorting, 1: sort on insertion).
	void SetDropDownListSortingMode(int sort);

	// Sets text colors of the value label and the dropdown list.
	// Parameters:
	// -> styleTextColor1_BGR: The first text color in BGR format.
	// -> styleTextColor2_BGR: The second text color in BGR format.
	void SetStyleText2Colors(int styleTextColor1_BGR, int styleTextColor2_BGR);

	// Returns the scroll bar.
	ScrollBarControl* GetDropDownScrollBar();

	// Returns the value label.
	LabelControl* GetValueLabel();

	// Returns the dropdown list box.
	ListBoxControl* GetDropDownList();

	// Adds the given item to the combo box list.
	// Parameters:
	// -> itemText: The displayed text.
	// -> itemId: The ID of the item to identify the selected one.
	bool AddItem(char *itemText, int itemId);

	// Sets the selected index.
	// Parameter:
	// -> index: The index of the item being selected.
	void SetSelectedIndex(int index);

	// Sets the selected item by its ID.
	// Parameter:
	// -> itemId: The ID of the item being selected.
	void SetSelectedItemId(int itemId);

	// Gets the selected item ID.
	int GetSelectedItemId();

	// Draws the combo box.
	void Draw();
};
#pragma pack(pop)