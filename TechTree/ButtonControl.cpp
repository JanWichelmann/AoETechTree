/* INCLUDES */

// Class header
#include "ButtonControl.h"

/* FUNCTIONS */

RECT ButtonControl::GetClientRectangle()
{
	// Return rectangle
	return _clientRectangle;
}

void ButtonControl::DrawSingle()
{
	// Call original function
	((void(__thiscall *)(ButtonControl *))0x00551920)(this);
}

void ButtonControl::SetHotKey(int hotKey, int shiftKeyModifierNeeded, int controlKeyModifierNeeded, int menuKeyModifierNeeded)
{
	// Set values
	_hotKey = hotKey;
	_shiftKeyModifierNeeded = shiftKeyModifierNeeded;
	_controlKeyModifierNeeded = controlKeyModifierNeeded;
	_menuKeyModifierNeeded = menuKeyModifierNeeded;
}

void ButtonControl::SetBackgroundSlpAtIndex(short backgroundIndex, Shape *backgroundSlp, short frameId)
{
	// Call original function
	((void(__thiscall *)(ButtonControl *, short, Shape *, short))0x00551350)(this, backgroundIndex, backgroundSlp, frameId);
}

void ButtonControl::SetDisplayMode(int mode)
{
	// Set display mode
	_displayMode = mode;
}

void ButtonControl::AssignLabelString(short index, char *labelString)
{
	// Call original function
	((void(__thiscall *)(ButtonControl *, short, char *))0x00551390)(this, index, labelString);
}