/* INCLUDES */

// Class header
#include "ComboBoxControl.h"

/* FUNCTIONS */

void ComboBoxControl::SetDropDownListSortingMode(int sort)
{
	// Call original function
	((void(__thiscall *)(ComboBoxControl *, int))0x00550720)(this, sort);
}

void ComboBoxControl::SetStyleText2Colors(int styleTextColor1_BGR, int styleTextColor2_BGR)
{
	// Set colors and do something unknown
	_dropDownList->SetStyleText2Colors(styleTextColor1_BGR, styleTextColor2_BGR);
	_dropDownList->sub_545D70(0);
	_dropDownList->sub_545DF0(1, 0x83);
	_valueLabel->SetStyleText2Colors(styleTextColor1_BGR, styleTextColor2_BGR);
	_valueLabel->sub_545D70(0);
	_valueLabel->sub_545DF0(1, 0x83);
}

ScrollBarControl* ComboBoxControl::GetDropDownScrollBar()
{
	// Return scrollbar
	return _dropDownListScrollBar;
}

bool ComboBoxControl::AddItem(char *itemText, int itemId)
{
	// Call original function
	return ((bool(__thiscall *)(ComboBoxControl *, char *, int))0x00550840)(this, itemText, itemId);
}

void ComboBoxControl::SetSelectedIndex(int index)
{
	// Call original function
	((void(__thiscall *)(ComboBoxControl *, int))0x00550740)(this, index);
}

void ComboBoxControl::SetSelectedItemId(int itemId)
{
	// Call original function
	((void(__thiscall *)(ComboBoxControl *, int))0x005507E0)(this, itemId);
}

void ComboBoxControl::Draw()
{
	// Call original function
	((void(__thiscall *)(ComboBoxControl *))0x0054F5B0)(this);
}

LabelControl* ComboBoxControl::GetValueLabel()
{
	// Return control
	return _valueLabel;
}

ListBoxControl* ComboBoxControl::GetDropDownList()
{
	// Return control
	return _dropDownList;
}

int ComboBoxControl::GetSelectedItemId()
{
	// Call original function
	return ((int(__thiscall *)(ComboBoxControl *))0x005509C0)(this);
}