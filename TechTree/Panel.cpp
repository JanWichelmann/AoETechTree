/* INCLUDES */

// Class header
#include "Panel.h"

/* FUNCTIONS */

void Panel::__Install()
{
	// First call base function
	base::__Install();
}

void Panel::Draw()
{
	// Call original function
	((void(__thiscall *)(Panel *))0x0055C710)(this);
}

bool Panel::CreateButtonWithOneFontWithTextFromDll(Panel *parentWindow, ButtonControl **destinationButtonPointer, int labelString0, int labelString1, int buttonPositionX, int buttonPositionY, int buttonWidth, int buttonHeight, int fontIndex, int interfaceSoundIndex, int unknown)
{
	// Call original function
	return ((bool(__thiscall *)(Panel *, Panel *, ButtonControl **, int, int, int, int, int, int, int, int, int))0x0055D4F0)(this, parentWindow, destinationButtonPointer, labelString0, labelString1, buttonPositionX, buttonPositionY, buttonWidth, buttonHeight, fontIndex, interfaceSoundIndex, unknown);
}

int Panel::HandleMouseMove(int cursorPosX, int cursorPosY, int controlKeyPressed, int shiftKeyPressed)
{
	// Call original function
	return ((int(__thiscall *)(Panel *, int, int, int, int))0x0055FD30)(this, cursorPosX, cursorPosY, controlKeyPressed, shiftKeyPressed);
}

int Panel::HandleMouseButtonDown(int buttonId, int cursorPosX, int cursorPosY, int controlKeyPressed, int shiftKeyPressed)
{
	// Call original function
	return ((int(__thiscall *)(Panel *, int, int, int, int, int))0x0055CB40)(this, buttonId, cursorPosX, cursorPosY, controlKeyPressed, shiftKeyPressed);
}